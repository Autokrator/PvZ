#include "regularzombie.h"
#include <QDebug>
#include "bullet.h"

RegularZombie::RegularZombie(QRect *spawn_row)
{
    xCordinate = 700;
    yCordinate = spawn_row->y();

    this->setPos(xCordinate,yCordinate);

    zombieImage = new QPixmap(":/Images/regularZombie");

    equipmentLife = 0;
    zombieLife = 10;
    damage = 1;
    attackRate = 500;
    xVelocity = 0.30;

    attackCounter = new QTime;

    collisionLine = new QGraphicsLineItem;
}

RegularZombie::~RegularZombie()
{
    delete zombieImage;
    delete attackCounter;
    delete collisionLine;
}

QRectF RegularZombie::boundingRect() const
{
    return QRectF(0,0,zombieImage->width(),zombieImage->height());
}

void RegularZombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //Paints zombie pixmap representation to screen with boundingRect as source and target rect
    if(!isSlowed)
        painter->drawPixmap(boundingRect(),*zombieImage,boundingRect());
    else
    {
        //Deletes current zombie image
        delete zombieImage;

        //Adjusted image if zombie is slowed
        zombieImage = new QPixmap(":/Images/regularZombieSlowed");
        painter->drawPixmap(boundingRect(),*zombieImage,boundingRect());
    }

}

void RegularZombie::advance(int phase)
{
    if(!phase) return;

    if(zombieLife <= 0)
    {
        delete this;
        return;
    }

    move(); //moves zombie based on velocity
    this->setPos(xCordinate,yCordinate); //updates pos
}

void RegularZombie::move()
{
    int y_adj = 20;
    collisionLine->setLine(xCordinate,yCordinate+y_adj,xCordinate+y_adj,yCordinate+y_adj);

    //Creates a list of items currently colliding with the mask
    QList<QGraphicsItem *> collision_list = scene()->collidingItems(collisionLine);

    //Checks for zombies colliding with mask and fires if there is atleast one zombie in row
    for(int i = 0; i < (int)collision_list.size();i++)
    {
        Plant * item = dynamic_cast<Plant *>(collision_list.at(i));
        if (item)
        {
            if(item->isTargetable)
            {
                if(attackCounter->isNull()) //Attacks and starts counter
                {
                    attackCounter->start();
                }
                else if(attackCounter->elapsed() >= attackRate) //attacks every 500 ms
                {
                    qDebug()<< attackCounter->elapsed();
                    attack(item);
                    attackCounter->restart(); //restarts counter
                }
            }
            else if(!item->isTargetable)
                xCordinate -= xVelocity;

            return;
        }
    }

    //Updates the x cordinate based on velocity
    xCordinate -= xVelocity;


}

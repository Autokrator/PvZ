#include "regularzombie.h"
#include <QDebug>

RegularZombie::RegularZombie(QRect *spawnRow)
{
    activeRow = *spawnRow;

    xCordinate = 500;
    yCordinate = spawnRow->y();

    this->setPos(xCordinate,yCordinate);

    zombieImage = new QPixmap(":/Images/regularZombie");

    equipmentLife = 0;
    zombieLife = 100;
    damage = 1;
    attackRate = 500;
    xVelocity = 0.1;

    attackCounter = new QTime;
}

RegularZombie::~RegularZombie()
{
    delete zombieImage;
    delete attackCounter;
}

QRectF RegularZombie::boundingRect() const
{
    return QRectF(0,0,zombieImage->width(),zombieImage->height());
}

void RegularZombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawRect(boundingRect());
    if(zombieLife > 0)
    {
        //Paints zombie pixmap representation to screen with boundingRect as source and target rect
        if(!isSlowed)
            painter->drawPixmap(boundingRect(),*zombieImage,boundingRect());
        else
        {
            //Deletes current zombie image
            delete zombieImage;
            zombieImage = NULL;

            //Adjusted image if zombie is slowed
            zombieImage = new QPixmap(":/Images/regularZombieSlowed");
            painter->drawPixmap(boundingRect(),*zombieImage,boundingRect());
        }
    }
    else
        delete this;
}

void RegularZombie::advance(int phase)
{
    if(!phase) return;

    move(); //moves zombie based on velocity
    this->setPos(xCordinate,yCordinate); //updates pos
}

void RegularZombie::move()
{
    collisionRect = new QGraphicsRectItem(this->x(),this->y()+zombieImage->height()/2,10,10);
    collisionRect->setPen(QPen(Qt::transparent));
    scene()->addItem(collisionRect);

    //Creates a list of items currently colliding with the mask
    QList<QGraphicsItem *> collision_list = scene()->collidingItems(collisionRect);

    delete collisionRect;
    collisionRect = NULL;

    //Checks for zombies colliding with mask and fires if there is atleast one zombie in row
    for(int i = 0; i < (int)collision_list.size();i++)
    {
        Plant * item = dynamic_cast<Plant *>(collision_list.at(i));
        if (item)
        {
            if(item->getPlantLife() > 0)
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
            return; //exits without changing xCordinate
        }
    }

    //Updates the x cordinate based on velocity
    xCordinate -= xVelocity;

}

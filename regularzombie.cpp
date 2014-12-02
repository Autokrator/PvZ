#include "regularzombie.h"
#include <QDebug>
#include "lawnmower.h"

RegularZombie::RegularZombie(QRect *spawn_row)
{
    xCordinate = spawn_row->x() + spawn_row->width();
    yCordinate = spawn_row->y();

    spawnRowX = spawn_row->x();

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

    //Deletes when health is below 0
    if(zombieLife <= 0)
    {
        delete this;
        return;
    }

    //change zombie image if zombie is attacking
    if(isAttacking)
    {
        delete zombieImage;
        zombieImage = new QPixmap(":/Images/regularzombieAttack");
        update();
    }
    else
    {
        delete zombieImage;
        zombieImage = new QPixmap(":/Images/regularZombie");
        update();
    }

    move(); //moves zombie based on velocity
    this->setPos(xCordinate,yCordinate); //updates pos

    //Checks if zombies are past homeblock
    if(this->x() < spawnRowX - zombieImage->width())
        zombiesWin = true;
}

void RegularZombie::move()
{
    int y_adj = 40;
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
                    attack(item);
                    attackCounter->restart(); //restarts counter
                    isAttacking = true;
                }
            }
            else if(!item->isTargetable)
            {
                xCordinate -= xVelocity;
                isAttacking = false;
            }

            return;
        }

        LawnMower *item2 = dynamic_cast<LawnMower *>(collision_list.at(i));
        if(item2)
        {
            item2->activateMovement();
            zombieLife -= 9999;
            return;
        }
    }

    //Updates the x cordinate based on velocity
    xCordinate -= xVelocity;
    isAttacking = false;


}

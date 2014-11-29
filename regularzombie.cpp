#include "regularzombie.h"

RegularZombie::RegularZombie(QRect *spawnRow)
{
    activeRow = *spawnRow;

    xCordinate = 1100;
    yCordinate = spawnRow->y();

    this->setPos(xCordinate,yCordinate);

    zombieImage = new QPixmap(":/Images/regularZombie");

    equipmentLife = 0;
    zombieLife = 10;
    damage = 1;
    attackRate = 500;
    xVelocity = 0.25;
}

QRectF RegularZombie::boundingRect() const
{
    return QRectF(0,0,zombieImage->width(),zombieImage->height());
}

void RegularZombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if(zombieLife >0)
        //Paints zombie pixmap representation to screen with boundingRect as source and target rect
        painter->drawPixmap(boundingRect(),*zombieImage,boundingRect());
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
    //Creates a list of items currently colliding with the mask
    QList<QGraphicsItem *> collision_list = scene()->collidingItems(this);


    //Checks for zombies colliding with mask and fires if there is atleast one zombie in row
    for(int i = 0; i < (int)collision_list.size();i++)
    {
        Plant * item = dynamic_cast<Plant *>(collision_list.at(i));
        if (item)
        {
            if(attackCounter.isNull()) //Attacks and starts counter
            {
                attack(item);
                attackCounter.start();
            }
            else if(attackCounter.elapsed() >= 500) //attacks every 500 ms
                attack(item);

            return;
        }
    }

    //Updates the x cordinate based on velocity
    xCordinate -= xVelocity;

}

void RegularZombie::attack(Plant *item)
{
    //Drecreases the health of the target plant
    item->decreaseHealth(damage);
}

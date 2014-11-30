#include "chomper.h"
#include "zombie.h"
#include <QDebug>

Chomper::Chomper(QRect *lawn_tile)
{
    //chomper properties
    life = 4;
    cost = 150;
    plantDamage = 150;
    fireRate = 42000;
    isEating = false;

    this->setPos(lawn_tile->x(),lawn_tile->y()+10);

    chomperImage  = new QPixmap(":/Images/chomper");
    chomperEatingImage = new QPixmap(":/Images/chomperEating");

    resetTimer = new QTime;
    resetTimer->start();

    int y_adj = 15; //This value is used to create a rect that is more centered in the lawn plot
                    //and thus zombie collision is more accurate since zombies in different lanes have a smaller
                    //chance of trigger collision events in another lane
    collisionRect = new QGraphicsRectItem(lawn_tile->x()+lawn_tile->width(),
                                          lawn_tile->y() + y_adj,
                                          lawn_tile->width()/2, //make the range of detection smaller in front of plant
                                                                //allow the zombie to be closer to center of tile before
                                                                //destroying it
                                          lawn_tile->height() - y_adj);
}

Chomper::~Chomper()
{
    delete chomperImage;

}

QRectF Chomper::boundingRect() const
{
   return QRectF(0,0,chomperImage->width(),chomperImage->height());
}

void Chomper::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawRect(boundingRect());
    if(!isEating)
        painter->drawPixmap(boundingRect(),*chomperImage,boundingRect());
    else
        painter->drawPixmap(boundingRect(),*chomperEatingImage,boundingRect());

}

void Chomper::advance(int phase)
{
    if(!phase) return;

    if(life <= 0)
    {
        delete this;
        return;
    }

    if(resetTimer->elapsed() >= fireRate && !isEating)
    {
        //Creates a list of items currently colliding with the mask
        QList<QGraphicsItem *> collision_list = scene()->collidingItems(collisionRect);

        //Checks for zombies colliding with mask and fires if there is atleast one zombie in row
        for(int i = 0; i < (int)collision_list.size(); i++)
        {
            Zombie * item = dynamic_cast<Zombie *>(collision_list.at(i));
            if (item)
            {
                item->decreaseLife(plantDamage);
                resetTimer->restart();
                isEating = true;
                update();
                return;
            }
        }
    }
    else if(isEating && resetTimer->elapsed() >= fireRate)
    {
        //Case when timer is above fire rate and no zombie in collision mask
        isEating = false;
        update();
    }
}

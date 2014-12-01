#include "chomper.h"
#include "zombie.h"
#include <QDebug>

int Chomper::seedingTime = 7500;

Chomper::Chomper(QRect *lawn_tile)
{
    //chomper properties
    life = 4;
    cost = 150;
    plantDamage = 150;
    fireRate = 42000;
    isEating = false; //intially chomper is not eating

    //Sets up position of chomper based on the tile it is planted on
    this->setPos(lawn_tile->x(),lawn_tile->y()+10 /*+10 used for better center to tile*/);

    //Sets ups pixmap for both states
    chomperImage  = new QPixmap(":/Images/chomper");
    chomperEatingImage = new QPixmap(":/Images/chomperEating");

    //Creates and starts counter
    resetTimer = new QTime;
    resetTimer->start();

    int y_adj = 15; //This value is used to create a rect that is more centered in the lawn plot
                    //and thus zombie collision is more accurate since zombies in different lanes have a smaller
                    //chance of trigger collision events in another lane
    //Making collision mask to detect zombie one tile infront of chomper's current tile
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
    delete chomperEatingImage;
    delete resetTimer;
}

QRectF Chomper::boundingRect() const
{
   return QRectF(0,0,chomperImage->width(),chomperImage->height());
}

void Chomper::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //Draws chomper pixmap based on what state it is in
    if(!isEating)
        painter->drawPixmap(boundingRect(),*chomperImage,boundingRect());
    else
        painter->drawPixmap(boundingRect(),*chomperEatingImage,boundingRect());

}

void Chomper::advance(int phase)
{
    if(!phase) return;

    //Deletes chomper if health is 0 or less
    if(life <= 0)
    {
        delete this;
        return;
    }

    //Checks to see if counter has reached the fireRate and chomper is not eating
    if(resetTimer->elapsed() >= fireRate && !isEating)
    {
        //Creates a list of items currently colliding with the mask
        QList<QGraphicsItem *> collision_list = scene()->collidingItems(collisionRect);

        //Checks for zombies colliding with mask
        for(int i = 0; i < (int)collision_list.size(); i++)
        {
            Zombie * item = dynamic_cast<Zombie *>(collision_list.at(i));
            if (item)
            {
                //Damages zombie, restarts timer and changes state
                item->decreaseLife(plantDamage);
                resetTimer->restart();
                isEating = true;

                update(); //updates chomper image since state just changed
                return;
            }
        }
    }
    //Checks to see if counter has reached the fireRate and chomper is eating
    else if(isEating && resetTimer->elapsed() >= fireRate)
    {
        //Used to revert chomper's active state and not eating zombie pixmap
        isEating = false;
        update();
    }
}

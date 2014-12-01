#include "potatomine.h"
#include "zombie.h"

Potatomine::Potatomine(QRect *lawn_tile)
{
    //potatomine properties
    life = 4;
    cost = 150;
    plantDamage = 90;
    fireRate = 100;
    detonate = false;

    this->setPos(lawn_tile->x(),lawn_tile->y()+20);

    potatomineImage = new QPixmap(":/Images/potatomine");
    explosionImage = new QPixmap(":/Images/explosion");

    explosionBoundedArea.setX(lawn_tile->x());
    /*Since zombies' bounding rects are a bit larger than one tile are most of the tile,
      it is safe to put the y as half the height of tile to avoid colliding with zombies
      that are a tiles away(vertical direction) from placed tile*/
    explosionBoundedArea.setY(lawn_tile->y() + lawn_tile->height()/2);
    explosionBoundedArea.setWidth(lawn_tile->width()/2); //so zombies are bit closer to center before dying
    explosionBoundedArea.setHeight(lawn_tile->height()/2);

    //Creates a rect that is about 3x3 with planted lawn_tile in the center
    explosionRect = new QGraphicsRectItem(explosionBoundedArea);

    readyTimer = new QTime;
    readyTimer->start();
}

Potatomine::~Potatomine()
{
    delete potatomineImage;
    delete explosionImage;
    delete readyTimer;
}

QRectF Potatomine::boundingRect() const
{
    return QRectF(0,0,potatomineImage->width(),potatomineImage->height());
}

void Potatomine::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if(!detonate)
        painter->drawPixmap(boundingRect(),*potatomineImage,boundingRect());
    else
    {
        painter->drawPixmap(boundingRect(),*explosionImage,boundingRect());
        delete this;
    }
}

void Potatomine::advance(int phase)
{
    if(!phase) return;

    if(life <= 0)
    {
        delete this;
        return;
    }

    if(readyTimer->elapsed() >= fireRate)
        isTargetable = false;
    else
        return;

    if(!isTargetable)
    {
        //Creates a list of items currently colliding with the mask
        QList<QGraphicsItem *> collision_list = scene()->collidingItems(explosionRect);

        //Checks for zombies colliding with mask and fires if there is atleast one zombie in row
        for(int i = 0; i < (int)collision_list.size(); i++)
        {
            Zombie * item = dynamic_cast<Zombie *>(collision_list.at(i));
            if (item)
            {
                item->decreaseLife(plantDamage);
                detonate = true;
                return;
            }
        }
    }

}

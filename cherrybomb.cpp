#include "cherrybomb.h"
#include "zombie.h"

Cherrybomb::Cherrybomb(QRect *lawn_tile)
{
    //cherrybomb properties
    life = 9999;
    cost = 150;
    plantDamage = 90;
    fireRate = 1;

    this->setPos(lawn_tile->x(),lawn_tile->y());

    cherrybombImage = new QPixmap(":/Images/cherrybomb");
    explosionImage = new QPixmap(":/Images/explosion");

    int explosion_radius = 3; //3x3 explosion
    explosionBoundedArea.setX(lawn_tile->x() - lawn_tile->width());
    /*Since zombies' bounding rects are a bit larger than one tile are most of the tile,
      it is safe to put the y as half the nieghbour tile to avoid colliding with zombies
      that are 2 tiles away(vertical direction) from placed tile*/
    explosionBoundedArea.setY(lawn_tile->y() - lawn_tile->height()/2);
    explosionBoundedArea.setWidth(lawn_tile->width()*explosion_radius);
    explosionBoundedArea.setHeight(lawn_tile->height()*2);

    //Creates a rect that is about 3x3 with planted lawn_tile in the center
    explosionRect = new QGraphicsRectItem(explosionBoundedArea);
}

Cherrybomb::~Cherrybomb()
{
    delete explosionRect;
    delete cherrybombImage;
    delete explosionImage;
}

QRectF Cherrybomb::boundingRect() const
{

    return QRectF(0,0,explosionImage->width(),explosionImage->height());
}

void Cherrybomb::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawRect(explosionBoundedArea);
    painter->drawPixmap(boundingRect(),*cherrybombImage,boundingRect());
    painter->drawPixmap(boundingRect(),*explosionImage,boundingRect());
}

void Cherrybomb::advance(int phase)
{
    if(!phase) return;

    //Creates a list of items currently colliding with the mask
    QList<QGraphicsItem *> collision_list = scene()->collidingItems(explosionRect);

    //Checks for zombies colliding with mask and fires if there is atleast one zombie in row
    for(int i = 0; i < (int)collision_list.size(); i++)
    {
        Zombie * item = dynamic_cast<Zombie *>(collision_list.at(i));
        if (item)
        {
            item->decreaseLife(plantDamage);
        }
    }

    plantDamage = 0; //So call to advance does not do damage more than once

    this->setOpacity(this->opacity()-0.01);
    if(this->opacity() <= 0)
        delete this;

}

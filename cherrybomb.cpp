#include "cherrybomb.h"
#include "zombie.h"

int Cherrybomb::seedingTime = 50000;

Cherrybomb::Cherrybomb(QRect *lawn_tile)
{
    //cherrybomb properties
    life = 9999;
    cost = 150;
    plantDamage = 90;
    fireRate = 1000;
    isTargetable = false; //makes cherrybomb untargetable
    isExploded = false; //initial state

    //Sets the position of cherrybomb based on selected lawn_tile
    this->setPos(lawn_tile->x(),lawn_tile->y());

    //loads pixmaps for cherrybomb and explosion
    cherrybombImage = new QPixmap(":/Images/cherrybomb");
    explosionImage = new QPixmap(":/Images/explosion");

    //Sets the explosion bounded area which is used to create collision mask
    int explosion_radius = 3; //3x3 explosion
    explosionBoundedArea.setX(lawn_tile->x() - lawn_tile->width());
    /*Since zombies' bounding rects are a bit larger than one tile are most of the tile,
      it is safe to put the y as half the nieghbour tile to avoid colliding with zombies
      that are 2 tiles away(vertical direction) from placed tile*/
    explosionBoundedArea.setY(lawn_tile->y() - lawn_tile->height()/2);
    explosionBoundedArea.setWidth(lawn_tile->width()*explosion_radius);
    explosionBoundedArea.setHeight(lawn_tile->height()*2);

    //Creates a graphics rect that is about 3x3 with planted lawn_tile in the center
    explosionRect = new QGraphicsRectItem(explosionBoundedArea);
}

Cherrybomb::~Cherrybomb()
{
    delete explosionRect;
    delete cherrybombImage;
    delete explosionImage;
}

QRectF Cherrybomb::boundingRect() const
{   //Uses the explosion image to generate a bounding rect
    return QRectF(0,0,explosionImage->width(),explosionImage->height());
}

void Cherrybomb::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //draws both pixmaps to the screen
    painter->drawPixmap(boundingRect(),*cherrybombImage,boundingRect());
    painter->drawPixmap(boundingRect(),*explosionImage,boundingRect());
}

void Cherrybomb::advance(int phase)
{
    if(!phase) return;

    if(!isExploded)
    {
        //Creates a list of items currently colliding with the mask
        QList<QGraphicsItem *> collision_list = scene()->collidingItems(explosionRect);

        //Checks for all zombies colliding with mask and decreases all their healths
        for(int i = 0; i < (int)collision_list.size(); i++)
        {
            Zombie * item = dynamic_cast<Zombie *>(collision_list.at(i));
            if (item)
                item->decreaseLife(plantDamage); //decreases hp of zombie
        }

        isExploded = true; //Updates state of cherrybomb to trigger animation
    }
    else
    {
        //Illusion of animation
        this->setOpacity(this->opacity() - 0.05);
        this->setScale(this->scale() + 0.01);

        if(this->opacity() <= 0)
            delete this; //deletes instance after opacity of item is 0
    }

}

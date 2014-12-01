#include "potatomine.h"
#include "zombie.h"

int Potatomine::seedingTime = 30000;

Potatomine::Potatomine(QRect *lawn_tile)
{
    //potatomine properties
    life = 4;
    cost = 150;
    plantDamage = 90;
    fireRate = 100;
    detonate = false;

    //Sets the position of potatomine based on selected lawn_tile
    this->setPos(lawn_tile->x(),lawn_tile->y()+20);

    //loads up pixmap of explosion and potatomine
    potatomineImage = new QPixmap(":/Images/potatomine");
    explosionImage = new QPixmap(":/Images/explosion");

    //Sets the explosion bounded area which is used to create collision mask
    explosionBoundedArea.setX(lawn_tile->x() + lawn_tile->width()/4);
    /*Since zombies' bounding rects are a bit larger than one tile are most of the tile,
      it is safe to put the y as half the height of tile to avoid colliding with zombies
      that are a tiles away(vertical direction) from placed tile*/
    explosionBoundedArea.setY(lawn_tile->y() + lawn_tile->height()/4);
    explosionBoundedArea.setWidth(lawn_tile->width()/2); //so zombies are bit closer to center before dying
    explosionBoundedArea.setHeight(lawn_tile->height()/2);

    //Creates a rect that is centered where at the planted lawn_tile
    explosionRect = new QGraphicsRectItem(explosionBoundedArea);

    //Makes and starts counter
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
    //Draws the potatomine pixmap to screen if detonate is false
    if(!detonate)
        //draws pixmap using boundingRect() as both source and target rect
        painter->drawPixmap(boundingRect(),*potatomineImage,boundingRect());
    else //Draws the explosion image
        //painter::drawPixmap overloaded function using QRect to autofit source pixmap into target rect
        painter->drawPixmap(QRect(0,0,potatomineImage->width(),potatomineImage->height()),
                            *explosionImage,
                            QRect(0,0,explosionImage->width(),explosionImage->height()));
}

void Potatomine::advance(int phase)
{
    if(!phase) return;

    //Delete potatomine instance if health is 0 or less
    if(life <= 0)
    {
        delete this;
        return;
    }

    //Makes potatomine untargetable after it's readyTimer has reached fireRate
    if(readyTimer->elapsed() >= fireRate)
        isTargetable = false;
    else //If counter has not reached fireRate yet
        return;

    if(detonate) //detonate animation
    {
        //Lowers opacity and increases scale
        this->setOpacity(this->opacity()-0.05);
        this->setScale(this->scale()+0.02);

        //Deletes object when opacity reaches 0 or less
        if(this->opacity() <= 0)
            delete this;

        return;
    }

    if(!isTargetable) //If potatomine is not targetable, it needs to check for zombies on collision mask
    {
        //Creates a list of items currently colliding with the mask
        QList<QGraphicsItem *> collision_list = scene()->collidingItems(explosionRect);

        //Checks for zombies colliding with mask
        for(int i = 0; i < (int)collision_list.size(); i++)
        {
            Zombie * item = dynamic_cast<Zombie *>(collision_list.at(i));
            if (item)
            {
                //Decreases zombie's hp
                item->decreaseLife(plantDamage);
                detonate = true; //updates state
            }
        }

        update(); //force repaint since state might have changed during for loop
    }

}

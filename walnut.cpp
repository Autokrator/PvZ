#include "walnut.h"

int Walnut::seedingTime = 30000;

Walnut::Walnut(QRect *plant_row)
{
    //walnut properties
    life = 72;
    cost = 50;
    plantDamage = 0;
    fireRate = 0;

    //Sets up position based on plant_row
    this->setPos(plant_row->x(),plant_row->y()+10);

    //loads walnut pixmap
    walnutImage = new QPixmap(":/Images/walnut");
}

Walnut::~Walnut()
{
    delete walnutImage;
}

QRectF Walnut::boundingRect() const
{
    return QRectF(0,0,walnutImage->width(),walnutImage->height());
}

void Walnut::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //draws walnutImage
    painter->drawPixmap(boundingRect(),*walnutImage,boundingRect());
}

void Walnut::advance(int phase)
{
    if(!phase) return;

    //Deletes instance if life is 0 or less
    if(life <= 0)
    {
        delete this;
        return;
    }
}

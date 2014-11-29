#include "walnut.h"

Walnut::Walnut(QRect *plant_row)
{
    //walnut properties
    life = 30;
    cost = 50;
    plantDamage = 0;
    fireRate = 0;

    this->setPos(plant_row->x(),plant_row->y()+10);
    walnutImage = new QPixmap(":/Images/walnut");
}

QRectF Walnut::boundingRect() const
{
    return QRectF(0,0,walnutImage->width(),walnutImage->height());
}

void Walnut::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if(life > 0)
        painter->drawPixmap(boundingRect(),*walnutImage,boundingRect());
    else
        delete this;
}

void Walnut::advance(int phase)
{
    if(!phase)
    {
        return;
    }
}

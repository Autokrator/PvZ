#include "walnut.h"

Walnut::Walnut(QRect *plant_row)
{
    //walnut properties
    life = 72;
    cost = 50;
    plantDamage = 0;
    fireRate = 0;

    this->setPos(plant_row->x(),plant_row->y()+10);
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
    painter->drawPixmap(boundingRect(),*walnutImage,boundingRect());

}

void Walnut::advance(int phase)
{
    if(!phase) return;

    if(life <= 0)
    {
        delete this;
        return;
    }
}

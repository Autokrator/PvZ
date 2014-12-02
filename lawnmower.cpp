#include "lawnmower.h"
#include <QDebug>

LawnMower::LawnMower(QRect *tile, int scene_width)
{
    lawnMowerImage = new QPixmap(":/Images/lawnMower");

    this->setPos(tile->x()-lawnMowerImage->width(),
                 tile->y() + 20);

    xVelocity = 7;
    isActivated = false;
    sceneEnd = scene_width;

}

LawnMower::~LawnMower()
{
    delete lawnMowerImage;
}

void LawnMower::activateMovement()
{
    isActivated = true;
}

QRectF LawnMower::boundingRect() const
{
    return QRectF(0,0,lawnMowerImage->width(),lawnMowerImage->height());
}

void LawnMower::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(boundingRect(),*lawnMowerImage,boundingRect());
}

void LawnMower::advance(int phase)
{
    if(!phase) return;

    if(isActivated)
        this->setX(this->x() + xVelocity);

    if(this->x() >= sceneEnd)
    {
        delete this;
        return;
    }
}


#include "bullet.h"
#include <QDebug>

Bullet::Bullet(bool slow, QGraphicsItem *parent)
{
    this->setPos(parent->x()+parent->boundingRect().width()/2,parent->y());
    xVelocity = 3;

    if(slow)
    {
        bulletImage = new QPixmap(":/Images/projectileSnowPea");
    }
    else
    {
        bulletImage = new QPixmap(":/Images/projectilePea");
    }
}

Bullet::~Bullet()
{
    delete bulletImage;
    qDebug() << "deleted image";
}

QRectF Bullet::boundingRect() const
{
    return QRectF(0,0,bulletImage->width(),bulletImage->height());
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(boundingRect(),*bulletImage,boundingRect());
}

void Bullet::advance(int phase)
{
    if(!phase)
        return;

    this->setPos(this->x()+xVelocity,this->y());
    if(this->x() >= 1320)
    {
        qDebug() << "deleted this";
        delete this;
    }
}

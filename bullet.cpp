#include "bullet.h"
#include <QDebug>

Bullet::Bullet(bool slow, Plant *parent)
{
    this->setPos(parent->x()+parent->boundingRect().width()/2,parent->y());
    xVelocity = 3;
    bulletDamage = parent->getDamage();

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

    //Creates a list of items currently colliding with the mask
    QList<QGraphicsItem *> collision_list = scene()->collidingItems(this);

    //Checks for zombies colliding with mask and fires if there is atleast one zombie in row
    for(int i = 0; i < (int)collision_list.size();i++)
    {
        Zombie * item = dynamic_cast<Zombie *>(collision_list.at(i));
        if (item)
        {
            item->decreaseLife(bulletDamage);
            delete this;
            return;
        }
    }

    this->setPos(this->x()+xVelocity,this->y());
}

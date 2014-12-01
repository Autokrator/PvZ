#include "bullet.h"
#include <QDebug>

Bullet::Bullet(bool slow, Plant *parent)
{
    this->setPos(parent->x()+parent->boundingRect().width()/2,parent->y());
    xVelocity = 3;
    bulletDamage = parent->getDamage();
    triggerSlow = slow;

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
}

void Bullet::destroyBullet()
{
    delete this;
}

QRectF Bullet::boundingRect() const
{
    return QRectF(0,0,bulletImage->width(),bulletImage->height());
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawRect(boundingRect());
    painter->drawPixmap(boundingRect(),*bulletImage,boundingRect());
}

void Bullet::advance(int phase)
{
    if(!phase)
        return;

    this->setPos(this->x()+xVelocity,this->y());

    //Creates a list of items currently colliding with the mask
    QList<QGraphicsItem *> collision_list = scene()->collidingItems(this);

    for(int i = 0; i < (int)collision_list.size(); i++)
    {
        //Checks for zombies colliding with mask
        Zombie * item = dynamic_cast<Zombie *>(collision_list.at(i));
        if(item)
        {
            item->decreaseLife(bulletDamage);

            if(triggerSlow && !item->getSlowStatus())
                item->setSlowEffect();


            delete this;
            return;
        }
    }
}

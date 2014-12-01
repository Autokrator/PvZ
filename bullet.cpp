#include "bullet.h"

Bullet::Bullet(bool slow, Plant *parent)
{
    //Uses the parent's position and boundingRect information to create a spawn location
    //which appears natural coming out of plant
    this->setPos(parent->x()+parent->boundingRect().width()/2,parent->y());
    this->setScale(0.9); /*sets scale of bullet instance, 0.9 allows for a smaller hitbox that is
                           more centered and thus ensures safety in not registering collisions with
                           zombies in neighbouring rows*/

    xVelocity = 3; //velocity of bullet
    bulletDamage = parent->getDamage(); //Uses damage of parent plant
    triggerSlow = slow; //checks if bullet will slow (default to false)

    if(slow) //Uses snowpea projectile if the bullet if slow is true
    {
        bulletImage = new QPixmap(":/Images/projectileSnowPea");
    }
    else //Uses normal green pea projectile if the bullet only damages
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
    //destroys instance of class
    delete this;
}

QRectF Bullet::boundingRect() const
{
    return QRectF(0,0,bulletImage->width(),bulletImage->height());
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //draws pixmap representation of bullet to screen
    painter->drawPixmap(boundingRect(),*bulletImage,boundingRect());
}

void Bullet::advance(int phase)
{
    if(!phase)
        return;

    //Updates position based on xVelocity
    this->setPos(this->x()+xVelocity,this->y());

    //Creates a list of items currently colliding with the bullet
    QList<QGraphicsItem *> collision_list = scene()->collidingItems(this);

    for(int i = 0; i < (int)collision_list.size(); i++)
    {
        //Checks for zombies colliding with the bullet
        Zombie * item = dynamic_cast<Zombie *>(collision_list.at(i));
        if(item)
        {
            //decreases the life of the zombie by the bulletDamage
            item->decreaseLife(bulletDamage);

            //triggers slow on zombie only if zombie has not already been slowed
            if(triggerSlow && !item->getSlowStatus())
                item->setSlowEffect();

            destroyBullet(); //destroys bullet
            return;
        }
    }
}

#include "peashooter.h"
#include <QDebug>

Peashooter::Peashooter(QRect *plant_row)
{
    life = 4;
    cost = 100;
    damage = 1;
    fireRate = 1500;
    slowEffect = false;

    this->setPos(plant_row->x(),plant_row->y());

    activeRow = *plant_row;
    peashooterImage = new QPixmap(":/Images/peashooter");
    fireCounter = new QTime;
}

Peashooter::~Peashooter()
{
    delete peashooterImage;
    delete fireCounter;
}

QRectF Peashooter::boundingRect() const
{
    return QRectF(0,0,peashooterImage->width(),peashooterImage->height());
}

void Peashooter::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(boundingRect(),*peashooterImage,boundingRect());
}

void Peashooter::advance(int phase)
{
    if(!phase) return;

    if(fireCounter->isNull())
        fireCounter->start();
    if(fireCounter->elapsed() >= 1500)
    {
        fireBullet();
        fireCounter->restart();
    }
}

void Peashooter::fireBullet()
{
//    //Creates a collision mask using the active row rectangle of currently placed plant
//    QGraphicsRectItem *collision_mask = new QGraphicsRectItem(activeRow);
//    collision_mask->setPen(QPen(Qt::transparent));
//    collision_mask->setBrush(QBrush(Qt::transparent));

//    scene()->addItem(collision_mask); //Adds mask to scene

//    //Creates a list of items currently colliding with the mask
//    QList<QGraphicsItem *> collision_list = scene()->collidingItems(collision_mask);

//    //Checks for zombies colliding with mask and fires if there is atleast one zombie in row
//    for(int i = 0; i < (int)collision_list.size();i++)
//    {
//        Zombie * item = dynamic_cast<Zombie *>(collision_list.at(i));
//        if (item)
//        {
//            //Fire a bullet in the row and exits function
            bullet = new Bullet(slowEffect,this);
            scene()->addItem(bullet);
//            return;
//        }
//    }

    //Reaches end of function if no zombies are in row and no bullet is fired in this case
}

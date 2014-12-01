#include "peashooter.h"
#include <QDebug>
#include "zombie.h"

Peashooter::Peashooter(QRect *plant_row, bool is_snowpea)
{
    //peashooter properties
    life = 10;
    plantDamage = 1;
    fireRate = 1500;
    slowEffect = is_snowpea;

    //setting the position of peashooter based on planting row
    this->setPos(plant_row->x(),plant_row->y() + 20);

    activeRow = *plant_row;

    if(!is_snowpea)
    {
        peashooterImage = new QPixmap(":/Images/peashooter");
        cost = 100;
    }
    else
    {
        peashooterImage = new QPixmap(":/Images/snowpea");
        cost = 175;
    }

    fireCounter = new QTime;
    fireCounter->start();

    /*Creates 2 points, one at the start of the plot where the peashooter is planted and
     one at the end of the scene; two createa straight line through the active row which
     acts like a collision mask that detects zombies and shoots when there is a zombie
     colliding with this invisible line*/

    //Creates 2 points using active row rectangle and peashooter image size
    QPoint p1(activeRow.x()+peashooterImage->width()/2,activeRow.y()+peashooterImage->height()/2);
    QPoint p2(activeRow.width()+activeRow.x(),activeRow.y()+peashooterImage->height()/2);

    //Creates a collision mask(line) using the points
    collisionLine = new QGraphicsLineItem(p1.x(),p1.y(),p2.x(),p2.y());
}

Peashooter::~Peashooter()
{
    delete peashooterImage;
    delete fireCounter;
    delete collisionLine;
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

    if(life <= 0)
    {
        delete this;
        return;
    }

    if(fireCounter->elapsed() >= fireRate)
    {
        fireBullet();
        fireCounter->restart();
    }
}

void Peashooter::fireBullet()
{ 
    //Creates a list of items currently colliding with the mask
    QList<QGraphicsItem *> collision_list = scene()->collidingItems(collisionLine);

    //Checks for zombies colliding with mask and fires if there is atleast one zombie in row
    for(int i = 0; i < (int)collision_list.size(); i++)
    {
        Zombie * item = dynamic_cast<Zombie *>(collision_list.at(i));
        if (item)
        {
            //Fire a bullet in the row and exits function
            bullet = new Bullet(slowEffect,this);
            bullet->setScale(0.9);
            scene()->addItem(bullet);
            return;
        }
    }
}

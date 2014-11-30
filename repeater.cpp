#include "repeater.h"

Repeater::Repeater(QRect *plant_row)
{
    //repeater properties
    life = 10;
    plantDamage = 1;
    fireRate = 1500;
    slowEffect = false;
    cost = 200;

    //setting the position of peashooter based on planting row
    this->setPos(plant_row->x(),plant_row->y());

    activeRow = *plant_row;

    repeaterImage = new QPixmap(":/Images/repeater");

    fireCounter = new QTime;
    fireCounter->start();

    /*Creates 2 points, one at the start of the plot where the peashooter is planted and
     one at the end of the scene; two createa straight line through the active row which
     acts like a collision mask that detects zombies and shoots when there is a zombie
     colliding with this invisible line*/

    //Creates 2 points using active row rectangle and peashooter image size
    QPoint p1(activeRow.x()+repeaterImage->width()/2,activeRow.y()+repeaterImage->height()/2);
    QPoint p2(activeRow.width()+activeRow.x(),activeRow.y()+repeaterImage->height()/2);

    //Creates a collision mask(line) using the points
    collisionLine = new QGraphicsLineItem(p1.x(),p1.y(),p2.x(),p2.y());
}

Repeater::~Repeater()
{
    delete repeaterImage;
    delete fireCounter;
    delete collisionLine;
}

QRectF Repeater::boundingRect() const
{
    return QRect(0,0,repeaterImage->width(),repeaterImage->height());
}

void Repeater::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

    painter->drawPixmap(boundingRect(),*repeaterImage,boundingRect());

}

void Repeater::advance(int phase)
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
        fireBullet();
        fireCounter->restart();
    }
}

void Repeater::fireBullet()
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
            scene()->addItem(bullet);
            return;
        }
    }

}

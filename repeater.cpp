#include "repeater.h"

Repeater::Repeater(QRect *plant_row)
{
    //repeater properties
    life = 10;
    plantDamage = 1;
    fireRate = 1500;
    slowEffect = false; //used to know which kind of bullet to use
    cost = 200;

    //setting the position of repeater based on planting row
    this->setPos(plant_row->x(),plant_row->y()+20);

    activeRow = *plant_row; //copies row information to activeRow member

    //loading repeater pixmap
    repeaterImage = new QPixmap(":/Images/repeater");

    fireCounter = new QTime;
    fireCounter->start();

    /*Creates 2 points, one at the start of the plot where the repeater is planted and
     one at the end of the scene; two create straight line through the active row which
     acts like a collision mask that detects zombies and shoots when there is a zombie
     colliding with this invisible line*/

    //Creates 2 points using active row rectangle and repeater image size
    QPoint p1(activeRow.x()+repeaterImage->width()/2,activeRow.y()+repeaterImage->height()/2);
    QPoint p2(activeRow.width()+activeRow.x(),activeRow.y()+repeaterImage->height()/2);

    //Creates a collision mask(line) using the points
    //Line starts from peashooter center and goes across the row
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
    //Draws repeater pixmap to screen using boundingRect() as source and target rect
    painter->drawPixmap(boundingRect(),*repeaterImage,boundingRect());
}

void Repeater::advance(int phase)
{
    if(!phase) return;

    //deletes repeater if health is 0 or less
    if(life <= 0)
    {
        delete this;
        return;
    }

    //When counter is above fireRate, two bullets are spawned and counter is restarted
    if(fireCounter->elapsed() >= fireRate)
    {
        //fires 2 bullets
        fireBullet();
        fireBullet();
        fireCounter->restart(); //restarts the counter
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

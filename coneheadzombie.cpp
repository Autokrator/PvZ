#include "coneheadzombie.h"

ConeHeadZombie::ConeHeadZombie(QRect *spawn_row)
{
    xCordinate = 700;
    yCordinate = spawn_row->y();

    this->setPos(xCordinate,yCordinate);

    zombieImage = new QPixmap(":/Images/conehead");

    equipmentLife = 18;
    zombieLife = 10;
    damage = 1;
    attackRate = 500;
    xVelocity = 0.30;

    attackCounter = new QTime;

    collisionLine = new QGraphicsLineItem;
}

ConeHeadZombie::~ConeHeadZombie()
{
    delete zombieImage;
    delete attackCounter;
    delete collisionLine;
}

QRectF ConeHeadZombie::boundingRect() const
{
    return QRectF(0,0,zombieImage->width(),zombieImage->height());
}

void ConeHeadZombie::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    //Paints zombie pixmap representation to screen with boundingRect as source and target rect
    if(!isSlowed)
        painter->drawPixmap(boundingRect(),*zombieImage,boundingRect());
    else
    {
        //Deletes current zombie image
        delete zombieImage;

        //Adjusted image if zombie is slowed
        zombieImage = new QPixmap(":/Images/coneheadSlowed");
        painter->drawPixmap(boundingRect(),*zombieImage,boundingRect());
    }
}

void ConeHeadZombie::advance(int phase)
{
    if(!phase) return;

    if(zombieLife <= 0)
    {
        delete this;
        return;
    }

    move(); //moves zombie based on velocity
    this->setPos(xCordinate,yCordinate); //updates pos
}

void ConeHeadZombie::move()
{
    int y_adj = 20;
    collisionLine->setLine(xCordinate,yCordinate+y_adj,xCordinate+y_adj,yCordinate+y_adj);

    //Creates a list of items currently colliding with the mask
    QList<QGraphicsItem *> collision_list = scene()->collidingItems(collisionLine);

    //Checks for zombies colliding with mask and fires if there is atleast one zombie in row
    for(int i = 0; i < (int)collision_list.size();i++)
    {
        Plant * item = dynamic_cast<Plant *>(collision_list.at(i));
        if (item)
        {
            if(item->isTargetable)
            {
                if(attackCounter->isNull()) //Attacks and starts counter
                {
                    attackCounter->start();
                }
                else if(attackCounter->elapsed() >= attackRate) //attacks every 500 ms
                {
                    attack(item);
                    attackCounter->restart(); //restarts counter
                }
            }
            else if(!item->isTargetable)
                xCordinate -= xVelocity;

            return;
        }
    }

    //Updates the x cordinate based on velocity
    xCordinate -= xVelocity;
}

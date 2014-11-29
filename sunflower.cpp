#include "sunflower.h"

Sunflower::Sunflower(QRect *plant_row)
{
    //sunflower properties
    life = 4;
    cost = 50;
    plantDamage = 0;
    fireRate = 24000;

    //Sets the position of sunflower based on the rectangle it is planted on
    this->setPos(plant_row->x(),plant_row->y());

    //loads the sunflower image
    sunflowerImage = new QPixmap(":/Images/sunflower");
    makeSunCounter = new QTime; //loads QTime counter
    makeSunCounter->start(); //starts the counter

}

Sunflower::~Sunflower()
{
    delete sunflowerImage;
    delete makeSunCounter;
    delete sun;
}

QRectF Sunflower::boundingRect() const
{
    return QRectF(0,0,sunflowerImage->width(),sunflowerImage->height());
}

void Sunflower::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if(life > 0)
        painter->drawPixmap(boundingRect(),*sunflowerImage,boundingRect());
    else
        delete this; //Deletes if health is lower than 0
}

void Sunflower::advance(int phase)
{
    if(!phase) return;

    //Checks to see if counter has reached the set firerate
    if(makeSunCounter->elapsed() >= fireRate)
    {
        //makes a new sun(type 2)
        sun = new Sun(this);
        scene()->addItem(sun);

        //Restarts the counter
        makeSunCounter->restart();
    }
}

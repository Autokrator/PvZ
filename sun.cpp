#include "sun.h"
#include <cmath>
#include <QDebug>
#define SWIDTH 1032
#define SHEIGHT 760

int Sun::sunPoints = 100;

Sun::Sun()
{
    //Loading image of sun
    sunImage = new QPixmap(":/Images/sun");

    //Setting up size based on sunImage
    sunSize.setHeight(sunImage->height());
    sunSize.setWidth(sunImage->width());

    //Setting intial position of sun
    position.setX(random(240,960-sunImage->width())); //range of x values = lawn width
    position.setY(0); //falls from '-'y so it is invisible till it enters scene
    this->setPos(position);

    //Setting velocity of sun
    xVelocity = 0;
    yVelocity = random(10,16); //Speed interval which when decreased by 0.2 increaments
                               //results in landing on the lawn tiles

    //Default not-clicked state
    isClicked = false;

    //Type 1: falls from sky
    type = 1;
}

Sun::Sun(QGraphicsItem *parent)
{
    //Loading image of sun
    sunImage = new QPixmap(":/Images/sun");

    //Setting up size based on sunImage
    sunSize.setHeight(sunImage->height());
    sunSize.setWidth(sunImage->width());

    //Setting intial position of sun
    position.setX(parent->x()); //takes the x location of parent
    position.setY(parent->y()); //takes the y location of parent
    this->setPos(position);

    //Setting velocity of sun
    xVelocity = 1;
    yVelocity = -10;
    yVelTemp = -1*yVelocity; //used to know when to stop moving sun

    //Default not-clicked state
    isClicked = false;

    //Type 2: produced by a plant
    type = 2;
}

Sun::~Sun()
{

}

int Sun::getSunPoints()
{
    return sunPoints;
}

void Sun::setSunPoints(int value)
{
    sunPoints = value;
}

void Sun::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if(!isClicked)
    {
        //Draws image if state is not clicked
        painter->drawPixmap(boundingRect(),*sunImage,boundingRect());
    }
    else if(isClicked)
    {
        //Removes image if state is clicked
        delete sunImage;
        sunImage = NULL;
        qDebug() << "img deleted";
    }
}

QRectF Sun::boundingRect() const
{
    //Creates a bounding rect the size of the image
    QPoint origin(0,0);
    return QRectF(origin,sunSize);
}

void Sun::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //Changes the state and calls paint to update object
    isClicked = true;
    update();
    updateSunPoints(25);
    QGraphicsItem::mousePressEvent(event);
}

void Sun::move(double time)
{
    //Appropriate move is applied based on type of sun
    if(yVelocity >= 0 && type == 1) //Moves until sun lands on lawn
    {
        //Calculates the new y coordinate (falling animation)
        position.setY(position.y() + round(yVelocity*time));
        yVelocity -= 0.2;
    }
    else if(type == 2)
    {
        //Comapres it to intial yVelocity and stops moving when condition is met
        if(yVelocity < yVelTemp)
        {
            //Calculates new position of sun
            position.setX(position.x() + round(xVelocity*time));
            position.setY(position.y() + round(yVelocity*time));

            //Increases the velocity so sun changes direction
            yVelocity += 0.5; //creates parabolic path when sun is spawned
        }
    }
}

void Sun::advance(int phase)
{
    if(phase == 0)
        return;

    //Moves the object according to velocity
    this->move(1);
    this->setPos(position); //updates position of GraphicsItem


}

void Sun::updateSunPoints(int change)
{
    //Increments/Decrements sunPoints
    sunPoints += change;
    qDebug() << sunPoints;
}

double Sun::random(double x1, double x2) const
{
    //Generating random number
    return x1 + (x2 - x1)*qrand()/(double(RAND_MAX)+1);

}

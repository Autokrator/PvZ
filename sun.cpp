#include "sun.h"
#include <cmath>
#include <QDebug>
#include <QGraphicsScene>

int Sun::sunPoints = 0; //Starting sunPoints
bool Sun::isPaused = false; //Starting state

Sun::Sun() : timeout(7500)
{
    //Loading image of sun
    sunImage = new QPixmap(":/Images/sun");

    //Setting up size based on sunImage
    sunSize.setHeight(sunImage->height());
    sunSize.setWidth(sunImage->width());

    //Setting intial position of sun
    position.setX(random(240,960-sunImage->width())); //range of x values = lawn width
    position.setY(-sunImage->height()); //falls from '-'y so it is invisible till it enters scene
    this->setPos(position);

    //Setting velocity of sun
    xVelocity = 0;
    yVelocity = 3;

    //Setting up yLand
    int lawn_start_y = 245; //y location of first lawn tile (row1,cloumn1)
    int lawn_start_height = 96; //height of each lawntile
    int lawn_rows = 5; //number of rows in the lawn
    yLand =random(lawn_start_y, //The landing must be between the first row and (last row - sunImage height)
                  lawn_start_y + lawn_start_height*lawn_rows - sunImage->height());

    //Default not-clicked state
    isClicked = false;

    //Setting the origin as the middle of sun image so rotation is about center
    this->setTransformOriginPoint(sunImage->width()/2.0,sunImage->height()/2.0);

    //Type 1: falls from sky
    type = 1;

    //Setting up counter and initialising rememberCounterTime
    counter = new QTime;
    rememberCounterTime = 0;
}

Sun::Sun(QGraphicsItem *parent) : timeout(7500)
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

    //Scaling it to 0 and setting origin as center of image
    this->setScale(0);
    this->setTransformOriginPoint(sunImage->width()/2.0,sunImage->height()/2.0);

    //Type 2: produced by a plant
    type = 2;

    //Setting up counter and rememberCounterTime
    counter = new QTime;
    rememberCounterTime = 0;
}

Sun::~Sun()
{
    delete sunImage;
    delete counter;
}

int Sun::getSunPoints()
{
    return sunPoints;
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
        //deletes current object
        delete this;
        return;
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
    QGraphicsItem::mousePressEvent(event);

    //Changes the state and calls paint to update object
    isClicked = true;
    update();

    //Updates the number of sunpoints the user now has
    updateSunPoints(25);
}

void Sun::move(double time)
{
    //Appropriate move is applied based on type of sun
    if(this->y() <= yLand && type == 1) //Moves until sun lands on yLand
    {
        //Calculates the new y coordinate (falling animation)
        position.setY(position.y() + round(yVelocity*time));

        //Rotation effect
        this->setRotation(this->rotation()+1);
    }
    //Compares it to intial yVelocity and stops moving when condition is met
    else if(type == 2 && yVelocity < yVelTemp)
    {
        //Increases scale to give a growing effect
        if(this->scale() <= 1)
            this->setScale(this->scale()+0.05);

        //Calculates new position of sun
        position.setX(position.x() + round(xVelocity*time));
        position.setY(position.y() + round(yVelocity*time));

        //Increases the velocity so sun changes direction
        yVelocity += 0.4; //creates parabolic path when sun is spawned

        //Rotation effect
        this->setRotation(this->rotation()+1);
    }
    else if(counter->isNull())
    {
        //Starts counter
        counter->start();
    }
    //Adjusts the timeout to account for pauses so time elasped isn't recounted
    else if(counter->elapsed() > timeout - rememberCounterTime)
    {
        //Deletes object after counter is greater than specified timeout
        delete this;
        return;
    }
}

void Sun::advance(int phase)
{
    if(phase == 0) return;

    if(!isPaused)
    {
        //Moves the object according to velocity
        this->move(1);
        this->setPos(position); //updates position of GraphicsItem
    }
    else
    {
        //In case of pause
        pause();
    }

}

void Sun::pause()
{
    if(counter->isNull())
        return; // Does nothing if counter has not started yet
    else
    {
        //Remembers the time elapsed by the pervious counter(s)
        rememberCounterTime += counter->elapsed();
        qDebug() << rememberCounterTime;

        //Creates a new counter and deletes old one
        delete counter;
        counter = new QTime;
    }
}

void Sun::updateSunPoints(int change)
{
    //Increments/Decrements sunPoints
    sunPoints += change;
}

double Sun::random(double x1, double x2) const
{
    //Generating random number
    return x1 + (x2 - x1)*qrand()/(double(RAND_MAX)+1);

}

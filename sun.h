#ifndef SUN_H
#define SUN_H
#include <QPainter>
#include <QGraphicsItem>
#include <QTime>

class Sun : public QGraphicsItem
{
public:
    //Creates two different types of sun depending on constructor
    Sun(); //Makes a sun that would fall from the sky
    Sun(QGraphicsItem *parent); //Makes a sun linked to another QGraphicsItem
    ~Sun(); //Used for memory management for each Sun object
    static int getSunPoints(); //Return the current value of the sunPoints
    static void updateSunPoints(int change); //Changes the sunPoints based on parameter
    static bool isPaused; //To indicate which state all sun objects must be in

private:
    static int sunPoints; //Holds the current value of sun points current player has
    double xVelocity; //control movement in x direction
    double yVelocity; //control movement in y direction
    double yLand; //final y position of type 1 sun
    double yVelTemp; //holds intial y velocity
    QPoint position; //Holds position of the object
    bool isClicked; //Indicates the state of sun object in relation to the mouse button
    QPixmap *sunImage; //Contains the pixmap information for each sun instance
    QSize sunSize; //Size of the sun pixmap
    int type; //Type 1 = default constructor (sky sun), type 2 = linked to graphicsitem (plant sun)
    QTime *counter; //Starts counts when sun reaches lawn
    const int timeout; //Time in ms until the sun is destroyed after reaching the lawn
    int rememberCounterTime; //Used to remember counter's progress after pauses
    void paint(QPainter*,const QStyleOptionGraphicsItem*, QWidget*);
    QRectF boundingRect() const; //Specifies bounding area for each sun
    void mousePressEvent(QGraphicsSceneMouseEvent *event); //When a sun's bounding area is clicked
    double random(double, double) const; //Generates a random number between two bounds
    void move(double time); //Moves sun based on it's type
    void advance(int phase);
    void pause(); //Used when game is paused to remember counter times
};

#endif // SUN_H


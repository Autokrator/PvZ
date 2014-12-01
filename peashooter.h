#ifndef PEASHOOTER_H
#define PEASHOOTER_H
#include "plant.h"
#include "bullet.h"

class Peashooter : public Plant
{
public:
    //Takes in a QRect row that gives information about plant location
    Peashooter(QRect *plant_row = 0, bool is_snowpea = false);
    ~Peashooter();
private:
    QPixmap *peashooterImage; //holds current pixmap representation of plant
    QRect activeRow; //the effective range of peashooter
    QTime *fireCounter; // controls bullet spawn
    Bullet *bullet; //holds bullet object when peashooter fires
    bool slowEffect; //used to know which type of bullet to use, also if snowpea or peashooter
    QGraphicsLineItem *collisionLine; //Used to detect zombies in plant's effective range
    void fireBullet(); //used to fire bullets if zombies are in range

    //Virtual QGraphicsItem functions
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void advance(int phase);
};

#endif // PEASHOOTER_H

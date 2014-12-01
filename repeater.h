#ifndef REPEATER_H
#define REPEATER_H
#include "plant.h"
#include "bullet.h"

class Repeater : public Plant
{
public:
    Repeater(QRect *plant_row = 0);
    ~Repeater();
    static int seedingTime; //cool down period after placing a plant
private:
    QPixmap *repeaterImage; //holds repeater pixmap
    Bullet *bullet; //holds bullet object when repeater fires
    QRect activeRow; //the effective range of repeater
    QTime *fireCounter; //counter used to create new bullets based on the fireRate
    bool slowEffect; //used to know which type of bullet to use
    QGraphicsLineItem *collisionLine; //collision mask used to detect if zombie is in the activeRow
    void fireBullet(); //used to fire bullets if zombies are in range

    //Virtual QGraphicsItem functions
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void advance(int phase);
};

#endif // REPEATER_H

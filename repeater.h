#ifndef REPEATER_H
#define REPEATER_H
#include "plant.h"
#include "bullet.h"

class Repeater : public Plant
{
public:
    Repeater(QRect *plant_row = 0);
    ~Repeater();
private:
    QPixmap *repeaterImage;
    Bullet *bullet;
    QRect activeRow;
    QTime *fireCounter;
    bool slowEffect;
    QGraphicsLineItem *collisionLine;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void advance(int phase);
    void fireBullet();
};

#endif // REPEATER_H

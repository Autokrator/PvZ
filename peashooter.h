#ifndef PEASHOOTER_H
#define PEASHOOTER_H
#include "plant.h"
#include "bullet.h"

class Peashooter : public Plant
{
public:
    Peashooter(QRect *plant_row = 0);
    ~Peashooter();
private:
    QPixmap *peashooterImage;
    QRect activeRow;
    QTime *fireCounter;
    Bullet *bullet;
    bool slowEffect;
    QGraphicsLineItem *collisionLine;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void advance(int phase);
    void fireBullet();
};

#endif // PEASHOOTER_H

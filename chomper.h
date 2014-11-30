#ifndef CHOMPER_H
#define CHOMPER_H
#include "plant.h"

class Chomper : public Plant
{
public:
    Chomper(QRect *lawn_tile = 0);
    ~Chomper();
private:
    QPixmap *chomperImage;
    QPixmap *chomperEatingImage;
    QGraphicsRectItem *collisionRect;
    QTime *resetTimer;
    bool isEating;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void advance(int phase);
};

#endif // CHOMPER_H

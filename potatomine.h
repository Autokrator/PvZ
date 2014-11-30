#ifndef POTATOMINE_H
#define POTATOMINE_H
#include "plant.h"

class Potatomine : public Plant
{
public:
    Potatomine(QRect* lawn_tile = 0);
    ~Potatomine();
private:
    QPixmap* potatomineImage;
    QPixmap* explosionImage;
    QGraphicsRectItem *explosionRect;
    QRect explosionBoundedArea;
    QTime *readyTimer;
    bool detonate;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void advance(int phase);
};

#endif // POTATOMINE_H

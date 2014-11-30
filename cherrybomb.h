#ifndef CHERRYBOMB_H
#define CHERRYBOMB_H
#include "plant.h"

class Cherrybomb : public Plant
{
public:
    Cherrybomb(QRect* lawn_tile = 0);
    ~Cherrybomb();
private:
    QPixmap* cherrybombImage;
    QPixmap* explosionImage;
    QGraphicsRectItem *explosionRect;
    QRect explosionBoundedArea;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void advance(int phase);
};

#endif // CHERRYBOMB_H

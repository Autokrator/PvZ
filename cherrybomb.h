#ifndef CHERRYBOMB_H
#define CHERRYBOMB_H
#include "plant.h"

class Cherrybomb : public Plant
{
public:
    Cherrybomb(QRect* lawn_tile = 0);
    ~Cherrybomb();
private:
    QPixmap* cherrybombImage; //holds cherrybomb pixmap
    QPixmap* explosionImage; //holds explosion pixmap
    QGraphicsRectItem *explosionRect; //Used as collision mask to damage all zombies caught
    QRect explosionBoundedArea;       //in the explosion
    bool isExploded; //to know state of cherrybomb

    //Virtual QGraphicsItem functions
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void advance(int phase);
};

#endif // CHERRYBOMB_H

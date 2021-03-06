#ifndef WALNUT_H
#define WALNUT_H
#include "plant.h"

class Walnut : public Plant
{
public:
    Walnut(QRect *plant_row = 0);
    ~Walnut();
    static int seedingTime; //cool down period after placing a plant
private:
    QPixmap *walnutImage; //holds walnut pixmap

    //Virtual QGraphicsItem functions
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void advance(int phase);
};

#endif // WALNUT_H

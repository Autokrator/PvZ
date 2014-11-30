#ifndef WALNUT_H
#define WALNUT_H
#include "plant.h"

class Walnut : public Plant
{
public:
    Walnut(QRect *plant_row = 0);
    ~Walnut();
private:
    QPixmap *walnutImage;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void advance(int phase);
};

#endif // WALNUT_H

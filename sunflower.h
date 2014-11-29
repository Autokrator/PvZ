#ifndef SUNFLOWER_H
#define SUNFLOWER_H
#include "plant.h"
#include "sun.h"

class Sunflower : public Plant
{
public:
    Sunflower(QRect *plant_row = 0);
    ~Sunflower();
private:
    QPixmap *sunflowerImage;
    Sun *sun;
    QTime *makeSunCounter;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void advance(int phase);
};

#endif // SUNFLOWER_H

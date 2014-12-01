#ifndef SUNFLOWER_H
#define SUNFLOWER_H
#include "plant.h"
#include "sun.h"

class Sunflower : public Plant
{
public:
    Sunflower(QRect *plant_row = 0);
    ~Sunflower();
    static int seedingTime; //cool down period after placing a plant
private:
    QPixmap *sunflowerImage; //holds sunflower pixmap
    Sun *sun; //holds sun object that is spawned every fireRate
    QTime *makeSunCounter; //Counter that is used to know when to spawn sun

    //Virtual QGraphicsItem functions
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void advance(int phase);
};

#endif // SUNFLOWER_H

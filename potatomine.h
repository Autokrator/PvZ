#ifndef POTATOMINE_H
#define POTATOMINE_H
#include "plant.h"

class Potatomine : public Plant
{
public:
    Potatomine(QRect* lawn_tile = 0);
    ~Potatomine();
private:
    QPixmap* potatomineImage; //holds potatomine pixmap
    QPixmap* explosionImage;  //holds explosion pixmap
    QGraphicsRectItem *explosionRect; //holds collision mask used to detect zombies in range
    QRect explosionBoundedArea; //bounded area where potatomine damage is effective
    QTime *readyTimer; //counter to change potatomine to untargetable state
    bool detonate; //detonate state used to know when to draw explosion

    //Virtual QGraphicsItem functions
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void advance(int phase);
};

#endif // POTATOMINE_H

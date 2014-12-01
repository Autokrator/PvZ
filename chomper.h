#ifndef CHOMPER_H
#define CHOMPER_H
#include "plant.h"

class Chomper : public Plant
{
public:
    Chomper(QRect *lawn_tile = 0);
    ~Chomper();
private:
    QPixmap *chomperImage; //holds chompher pixmap
    QPixmap *chomperEatingImage; //holds chomper eating pixmap
    QGraphicsRectItem *collisionRect; //collision mask used to detect zombie
                                      //in chomper's effective range
    QTime *resetTimer; //counter used to reset chomper states
    bool isEating; //chomper state where chomper is inactive and cannot attack

    //Virtual QGraphicsItem functions
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void advance(int phase);
};

#endif // CHOMPER_H

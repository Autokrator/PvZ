#ifndef CONEHEADZOMBIE_H
#define CONEHEADZOMBIE_H
#include "zombie.h"

class ConeHeadZombie : public Zombie
{
public:
    ConeHeadZombie(QRect *spawn_row = 0);
    ~ConeHeadZombie();
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void advance(int phase);
    void move();


};

#endif // CONEHEADZOMBIE_H

#ifndef FLAGZOMBIE_H
#define FLAGZOMBIE_H
#include "zombie.h"

class FlagZombie : public Zombie
{
public:
    FlagZombie(QRect *spawn_row = 0);
    ~FlagZombie();
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void advance(int phase);
    void move();
};

#endif // FLAGZOMBIE_H

#ifndef REGULARZOMBIE_H
#define REGULARZOMBIE_H
#include "zombie.h"

class RegularZombie : public Zombie
{
public:
    RegularZombie(QRect *spawn_row = 0);
    ~RegularZombie();

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void advance(int phase);
    void move();
};

#endif // REGULARZOMBIE_H

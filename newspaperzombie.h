#ifndef NEWSPAPERZOMBIE_H
#define NEWSPAPERZOMBIE_H
#include "zombie.h"

class NewspaperZombie : public Zombie
{
public:
    NewspaperZombie(QRect *spawn_row = 0);
    ~NewspaperZombie();
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void advance(int phase);
    void move();
};

#endif // NEWSPAPERZOMBIE_H

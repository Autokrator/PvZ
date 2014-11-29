#ifndef REGULARZOMBIE_H
#define REGULARZOMBIE_H
#include "zombie.h"

class RegularZombie : public Zombie
{
public:
    RegularZombie(QRect *spawnRow = 0);

private:
    QPixmap *zombieImage;
    QRect activeRow;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void advance(int phase);
    void move();
    void attack(Plant *item);

};

#endif // REGULARZOMBIE_H

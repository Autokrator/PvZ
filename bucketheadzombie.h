#ifndef BUCKETHEADZOMBIE_H
#define BUCKETHEADZOMBIE_H
#include "zombie.h"

class BucketHeadZombie : public Zombie
{
public:
    BucketHeadZombie(QRect *spawn_row = 0);
    ~BucketHeadZombie();
private:
    void move();
    void updateImage();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void advance(int phase);
};

#endif // BUCKETHEADZOMBIE_H

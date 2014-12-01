#ifndef BULLET_H
#define BULLET_H
#include "zombie.h"

class Bullet : public QGraphicsItem
{
public:
    Bullet(bool slow = false, Plant *parent = 0);
    ~Bullet();
    int bulletDamage; //holds bulletDamage(passed down by plant parent)
    bool triggerSlow; //holds logic value to trigger slow or not
    void destroyBullet(); //deletes the current instance of the bullet

private:
    QPixmap *bulletImage; //holds pixmap representation of bullet
    double xVelocity; //the x velocity at which the bullet travels at

    //Virtual QGraphicsItem functions
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void advance(int phase);
};

#endif // BULLET_H

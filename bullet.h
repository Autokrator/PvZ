#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>

class Bullet : public QGraphicsItem
{
public:
    Bullet(bool slow = false,QGraphicsItem* parent = 0);
    ~Bullet();
private:
    QPixmap *bulletImage;
    double xVelocity;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void advance(int phase);
};

#endif // BULLET_H

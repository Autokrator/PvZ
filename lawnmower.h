#ifndef LAWNMOWER_H
#define LAWNMOWER_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>

class LawnMower : public QGraphicsItem
{
public:
    LawnMower(QRect *tile = 0,int scene_width = 0);
    ~LawnMower();
    void activateMovement();
private:
    QPixmap *lawnMowerImage;
    int sceneEnd;
    double xVelocity;
    bool isActivated;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void advance(int phase);

};

#endif // LAWNMOWER_H

#ifndef SUN_H
#define SUN_H
#include <QPainter>
#include <QGraphicsItem>

class Sun : public QGraphicsItem
{
public:
    Sun();
    Sun(QGraphicsItem *parent);
    ~Sun();
    static int getSunPoints();
    static void setSunPoints(int value);

private:
    static int sunPoints; //
    double xVelocity;
    double yVelocity;
    double yVelTemp;
    QPoint position;
    bool isClicked;
    QPixmap *sunImage;
    QSize sunSize;
    int type;
    void paint(QPainter*,const QStyleOptionGraphicsItem*, QWidget*);
    QRectF boundingRect() const;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    double random(double, double) const;
    void move(double time);
    void advance(int phase);
    void updateSunPoints(int);
};

#endif // SUN_H


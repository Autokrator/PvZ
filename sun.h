#ifndef SUN_H
#define SUN_H
#include <QPainter>
#include <QGraphicsItem>
#include <QTime>

class Sun : public QGraphicsItem
{
public:
    Sun();
    Sun(QGraphicsItem *parent);
    ~Sun();
    static int getSunPoints();
    static bool isPaused;
    static void setSunPoints(int value);
    static void updateSunPoints(int change);

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
    QTime *counter;
    const int timeout;
    int rememberCounterTime;
    void paint(QPainter*,const QStyleOptionGraphicsItem*, QWidget*);
    QRectF boundingRect() const;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    double random(double, double) const;
    void move(double time);
    void advance(int phase);
    void pause();
};

#endif // SUN_H


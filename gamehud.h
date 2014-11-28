#ifndef GAMEHUD_H
#define GAMEHUD_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMouseEvent>
#include "sun.h"

class GameHud : public QGraphicsItem
{
public:
    GameHud();
    QString user;
    QString level;
    static int mouseState; /*Used to indicate plant selection
                             0 = default, 1 = peashooter, 2 = sunflower... 8*/

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void advance(int phase);
    void mousePressEvent(QGraphicsSceneMouseEvent *e);
    void resetCardOpacities();

    //Plant selection cards used to know which plant is selected or can be selected
    QGraphicsPixmapItem *peashooterCard;
    QGraphicsPixmapItem *sunflowerCard;
    QGraphicsPixmapItem *cherrybombCard;
    QGraphicsPixmapItem *walnutCard;
    QGraphicsPixmapItem *repeaterCard;
    QGraphicsPixmapItem *chomperCard;
    QGraphicsPixmapItem *snowpeashooterCard;
    QGraphicsPixmapItem *potatomineCard;
};

#endif // GAMEHUD_H

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
    ~GameHud();
    QString user;
    QString level;

private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void advance(int phase);
};

#endif // GAMEHUD_H

#ifndef PLANT_H
#define PLANT_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QTime>

class Plant : public QGraphicsItem
{
public:
    Plant();
protected:
    int life;
    int cost;
    double damage;
    double fireRate;
};

#endif // PLANT_H

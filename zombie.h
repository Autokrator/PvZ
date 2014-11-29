#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QTime>
#include "plant.h"

class Zombie : public QGraphicsItem
{
public:
    Zombie();
    void decreaseLife(int value);

protected:
    double xCordinate;
    int yCordinate;
    int equipmentLife;
    int zombieLife;
    int damage;
    int attackRate;
    double xVelocity;
    bool isSlowed;
    QTime attackCounter;
    virtual void attack(Plant*) = 0;
    virtual void move() = 0;
};

#endif // ZOMBIE_H

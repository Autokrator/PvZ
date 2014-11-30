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
    void setSlowEffect();
    bool getSlowStatus() const;

protected:
    double xCordinate;
    int yCordinate;
    int equipmentLife;
    int zombieLife;
    int damage;
    int attackRate;
    double xVelocity;
    bool isSlowed;
    QTime *attackCounter;
    void attack(Plant*item);
    virtual void move();
};

#endif // ZOMBIE_H

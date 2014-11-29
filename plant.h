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
    void decreaseHealth(int value);
    int getDamage() const;
    int getPlantLife() const;
protected:
    int life;
    int cost;
    double plantDamage;
    double fireRate;
};

#endif // PLANT_H

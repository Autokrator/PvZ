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
    ~Plant();
    void decreaseHealth(int value); //decreases health of plant by value
    double getDamage() const; //return plantDamage
    int getPlantLife() const; //returns current life of plant
    int getCost() const; //returns cost of plant
    bool isTargetable; //classifies if plant can be targetted by zombies
protected:
    int life; //how much damage each plant can take
    int cost; //how many sun points it costs to plant
    double plantDamage; //how much damage the plant does
    double fireRate; //what rate is the damage applied (in ms)
};

#endif // PLANT_H

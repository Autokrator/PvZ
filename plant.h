#ifndef PLANT_H
#define PLANT_H
#include <QGraphicsItem>
#include <QTime>

class Plant : public QGraphicsItem
{
public:
    Plant();
    void decreaseHealth(int value);
    int getDamage() const;
protected:
    int life;
    int cost;
    double damage;
    double fireRate;
};

#endif // PLANT_H

#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "plant.h"

class Zombie : public QGraphicsItem
{
public:
    Zombie();
    void decreaseLife(int value); //Decreases the total health of zombie based on value
    void setSlowEffect(); //decreases the current velocity of zombie by 50% and sets isSlowed as true
    bool getSlowStatus() const; //retunr isSlowed status condition of zombie

protected:
    double xCordinate; //x coordinate of zombie
    int yCordinate; //y coordinate of zombie
    int equipmentLife; //life of equipment
    int zombieLife; //life of the zombie
    int damage; //zombie damage per attack
    int attackRate; //rate(ms) at which zombie attacks
    double xVelocity; //velocity in x direction
    bool isSlowed; //status conidition used to prevent slowing mutiple times
    bool isAttacking; //is true whenever zombie is in combat with plant
    QPixmap *zombieImage; //holds zombie pixmap data
    QGraphicsLineItem *collisionLine; //collision line used to detect plants in a small line in front of zombie
    QTime *attackCounter; //counter that only allows zombie to attack after their attackRate has elapsed
    void attack(Plant *item); //used to attack plant
    virtual void move(); //used to define zombie movement when advance slot of each zombie is called
};

#endif // ZOMBIE_H

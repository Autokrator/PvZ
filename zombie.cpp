#include "zombie.h"
#include <QDebug>

int Zombie::zombiesAlive = 0;
bool Zombie::zombiesWin = false;

Zombie::Zombie()
{
    //Intially all zombies are not slowed and are not attacking
    isSlowed = false;
    isAttacking = false;

    //Adds one to number of zombies alive
    zombiesAlive++;
}

Zombie::~Zombie()
{
    --zombiesAlive;
    qDebug() << zombiesAlive;
}

void Zombie::decreaseLife(int value)
{
    //Drecreases life of zombie, first the equipment then zombie
    equipmentLife -= value;
    if(equipmentLife <= 0)
    {
        zombieLife += equipmentLife;
        equipmentLife = 0;
    }
}

void Zombie::setSlowEffect()
{
    //decreases the velocity by 50%
    this->isSlowed = true;
    xVelocity *= 0.5;
}

bool Zombie::getSlowStatus() const
{
    return isSlowed;
}

void Zombie::attack(Plant *item)
{
    //Decreases the hp of plant
    item->decreaseHealth(damage);
}

void Zombie::move()
{

}

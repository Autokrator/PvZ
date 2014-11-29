#include "zombie.h"

Zombie::Zombie()
{
    //Intially all zombies are not slowed
    isSlowed = false;
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
    this->isSlowed = true;
    xVelocity *= 0.5;
}

bool Zombie::getSlowStatus() const
{
    return isSlowed;
}

void Zombie::attack(Plant *item)
{
    item->decreaseHealth(damage);
}

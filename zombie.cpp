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

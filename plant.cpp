#include "plant.h"

Plant::Plant()
{

}

void Plant::decreaseHealth(int value)
{
    //Decreases the health of plant
    life -= value;
}

int Plant::getDamage() const
{
    return damage;
}

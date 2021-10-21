#pragma once
#include "Creature.h"
class Player :
    public Creature
{
public:
    Player();
    int noKeys;
    int Gold;
    void PerformAttack(vector<Entity*>& hits);
};


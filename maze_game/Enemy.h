#pragma once
#include "Creature.h"
class Enemy : public Creature
{
public:
	Enemy();
	int damage;
	void  Behaviour(float fElapsedTime, Entity* player);
};


#pragma once

#include "Entity.h"
#include "Sword.h"



class Creature : public Entity
{
protected:
	olcSprite* spriteCreature;

	enum { SOUTH = 0, WEST = 1, NORTH = 2, EAST = 3 } facingDirection;

public:

	int nHealth;
	int nHealthMax;
	bool isDead;
	Sword* sword;

	Creature(string name, olcSprite* sprite);

	void DrawSelf(olcConsoleGameEngineOOP* gfx, float ox, float oy) override;
	void Update(float fElapsedTime, Entity* player = nullptr) override;
	void OnInteract(Entity* player = nullptr) override;
	virtual void  Behaviour(float fElapsedTime, Entity* player);

	int GetFacingDirection();

};


#include "Creature.h"


Creature::Creature(string name, olcSprite* sprite) : Entity(name)
{
	sword = nullptr;
	spriteCreature = sprite;
	nHealth = 10;
	nHealthMax = 10;
	facingDirection = SOUTH;
	isDead = false;

}

void Creature::OnInteract(Entity* player)
{
	return;
}


void Creature::DrawSelf(olcConsoleGameEngineOOP* gfx, float ox, float oy)
{
	int nSheetOffsetX = 0;
	int nSheetOffsetY = 0;

	if (facingDirection == WEST)
	{
		nSheetOffsetX = 1 * 16;
		nSheetOffsetY = 0;
	}
	else if (facingDirection == EAST)
	{
		nSheetOffsetX = 3 * 16;
		nSheetOffsetY = 0;
	}
	else if (facingDirection == NORTH)
	{
		nSheetOffsetX = 2 * 16;
		nSheetOffsetY = 0;
	}
	else if (facingDirection == SOUTH)
	{
		nSheetOffsetX = 0;
		nSheetOffsetY = 0;
	}


	gfx->DrawPartialSprite((Px - ox) * 16.0f, (Py - oy) * 16.0f, spriteCreature, nSheetOffsetX, nSheetOffsetY, 16, 16);

}


void Creature::Update(float fElapsedTime, Entity* player)
{

	if (Vx < 0.0f) facingDirection = WEST;
	if (Vx > 0.0f) facingDirection = EAST;
	if (Vy < -0.0f) facingDirection = NORTH;
	if (Vy > 0.0f) facingDirection = SOUTH;


	Behaviour(fElapsedTime, player);
}


void Creature::Behaviour(float fElapsedTime, Entity* player)
{
	// no default behaviour
}

int Creature::GetFacingDirection()
{
	return facingDirection;
}


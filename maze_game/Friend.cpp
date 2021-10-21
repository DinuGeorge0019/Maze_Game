#include "Friend.h"
#include "Player.h"

Friend::Friend() : Creature("friend", new olcSprite(L"Sprites/friend.spr"))
{

	friendly = true;
	keys = rand()% (3 - 1) + 2;
	
}

void Friend::DrawSelf(olcConsoleGameEngineOOP* gfx, float ox, float oy)
{

	gfx->DrawPartialSprite((Px - ox) * 16.0f, (Py - oy) * 16.0f, spriteCreature, 4 * 16, 0 * 16, 16, 16);

}

void Friend::Update(float fElapsedTime, Entity* player)
{
	// no update
	return;
}

void Friend::Behaviour(float fElapsedTime, Entity* player)
{
	// no update
	return;
}


void Friend::OnInteract(Entity* player)
{
	// no update
	Player* player_obj = dynamic_cast<Player*>(player);
	player_obj->noKeys += keys;
	isRedundant = true;
	return;
}

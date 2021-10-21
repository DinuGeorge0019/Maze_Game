#include "Player.h"
Player::Player() : Creature("player", new olcSprite(L"Sprites/character.spr"))
{
	Px = 1.0f;
	Py = 1.0f;
	sword = new Sword(5);

	noKeys = 0;
	Gold = 0;

}

void Player::PerformAttack(vector<Entity*>& hits)
{
	if (sword == nullptr)
	{
		return;
	}

	sword->OnUse(this, hits);
}
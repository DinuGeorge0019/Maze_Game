#include "Enemy.h"
#include "Player.h"
Enemy::Enemy() : Creature("enemy", new olcSprite(L"Sprites/enemy.spr"))
{
	friendly = false;
	nHealth = 10;
	nHealthMax = 10;
	damage = 2;
}


void Enemy::Behaviour(float fElapsedTime, Entity* player)
{

	float targetPx = player->Px - Px;
	float targetPy = player->Py - Py;

	float distance = sqrt(targetPx * targetPx + targetPy * targetPy);

	if (distance < 6.0f)
	{
		Vx = (targetPx/ distance) * 2.0f;
		Vy = (targetPy / distance) * 2.0f;
	}
	else
	{
		Vx = 0;
		Vy = 0;
	}

	Player* player_obj = dynamic_cast<Player*>(player);
	//do damage to player
	if (player_obj->Px < (Px + 1.0f) && (player_obj->Px + 1.0f) > Px &&
		player_obj->Py < (Py + 1.0f) && (player_obj->Py + 1.0f) > Py)
	{
		player_obj->nHealth -= damage;
		isDead = true;
	}


}
#include "Sword.h"
#include "Creature.h"


Sword::Sword(int dmg) : Entity("sword")
{
	damage = dmg;
	this->duration = 0.1f;
}

Sword::Sword(int dmg, float ox, float oy, float velx, float vely, float duration) : Entity("sword")
{
	damage = dmg;
	Px = ox;
	Py = oy;
	Vx = velx;
	Vy = vely;
	this->duration = duration;
}

bool Sword::OnUse(Entity* object, vector<Entity*>& hits)
{
	
	Creature* aggressor = dynamic_cast<Creature*>(object);

	float x = 1, y = 1;

	if (aggressor->GetFacingDirection() == 0) // South
	{
		x = aggressor->Px;
		y = aggressor->Py + 1.0f;
	}

	if (aggressor->GetFacingDirection() == 1) // East
	{
		x = aggressor->Px - 1.0f;
		y = aggressor->Py;
	}

	if (aggressor->GetFacingDirection() == 2) // North
	{
		x = aggressor->Px;
		y = aggressor->Py - 1.0f;
	}

	if (aggressor->GetFacingDirection() == 3) // West
	{
		x = aggressor->Px + 1.0f;
		y = aggressor->Py;
	}

	Sword* new_hit = new Sword(damage, x, y, aggressor->Vx, aggressor->Vy, 0.1f);

	hits.push_back(new_hit);


 	return false;
}

void Sword::DrawSelf(olcConsoleGameEngineOOP* gfx, float ox, float oy)
{
	gfx->DrawPartialSprite((Px - ox) * 16, (Py - oy) * 16, new olcSprite(L"Sprites/Sword.spr"), 0, 0, 16, 16);

}

void Sword::Update(float fElapsedTime, Entity* player)
{
	duration -= fElapsedTime;
	if (duration <= 0.0f)
		isRedundant = true;
}

void Sword::OnInteract(Entity* player)
{


}
#include "Entity.h"

Entity::Entity(string name)
{
	this->name = name;
	Px = 0.0f;
	Py = 0.0f;
	Vx = 0.0f;
	Vy = 0.0f;

	friendly = true;
	isRedundant = false;

}
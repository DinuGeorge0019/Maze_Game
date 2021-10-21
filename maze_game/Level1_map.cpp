#include "Level1_map.h"

Level1_map::Level1_map(vector<Entity*>& creatures)
{
	CreateMap("level1.txt", "level1");

	srand((unsigned)time(NULL));

	// Populate map with enemies
	for (int i = 0; i < 50; i++)
	{
		Enemy* e = new Enemy();
		e->Px = rand() % 64;
		e->Py = rand() % 40;
		creatures.push_back(e);
	}

	// Populate map with friends
	for (int i = 0; i < 5; i++) // MODIFY TO 5
	{
		Friend* f = new Friend();
		f->Px = rand() % 64;
		f->Py = rand() % 40;
		creatures.push_back(f);
	}

}
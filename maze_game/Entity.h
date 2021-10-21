#pragma once

#include <string>
#include <iostream>
#include "olcConsoleGameEngine.h"
using namespace std;

class Entity
{

public:
	// Entity Properties
	float Px, Py;
	float Vx, Vy;

	bool friendly;
	bool isRedundant;

	string name;

	Entity(string name);

	virtual void DrawSelf(olcConsoleGameEngineOOP* gfx, float ox, float oy) = 0;
	virtual void Update(float fElapsedTime, Entity* player = nullptr) = 0;
	virtual void OnInteract(Entity* player = nullptr) = 0;

};

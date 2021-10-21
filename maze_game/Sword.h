#pragma once

#include "Entity.h"

class Sword : public Entity
{
public:

    int damage;
    float duration;

    Sword(int dmg);
    Sword(int dmg, float ox, float oy, float velx, float vely, float duration);

    bool OnUse(Entity* object, vector<Entity*>& hits);

    void DrawSelf(olcConsoleGameEngineOOP* gfx, float ox, float oy) override;
    void Update(float fElapsedTime, Entity* player = nullptr) override;
    void OnInteract(Entity* player = nullptr) override;

};


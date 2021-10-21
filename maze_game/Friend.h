#pragma once
#include "Creature.h"
class Friend :
    public Creature
{
public:
    Friend();
    int keys;

    void DrawSelf(olcConsoleGameEngineOOP* gfx, float ox, float oy) override;
    void Update(float fElapsedTime, Entity* player = nullptr) override;
    void OnInteract(Entity* player = nullptr) override;
    void Behaviour(float fElapsedTime, Entity* player) override;
};


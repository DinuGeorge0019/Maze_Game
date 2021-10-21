#pragma once

#include "olcConsoleGameEngine.h"
#include "Camera_view.h"
#include "Tile.h"
#include "Maps.h"
#include "Creature.h"
#include "Entity.h"
#include "Player.h"
#include "Level1_map.h"
#include <string>
#include <fstream>
#include <vector>

using namespace std;


class Maze_game : public olcConsoleGameEngineOOP
{

private:
	static Maze_game* game_instace;
	Maze_game();
	
	//maps
	Maps* level;

	// player properties
	Player* player;

	//Creatures
	vector<Entity*> creatures;

	vector<Entity*> hits;


	//camera and tiles
	Camera_view camera_view;
	Tile tile_data;

	olcSprite* spriteFont;
	olcSprite* spriteMap;
	olcSprite* striteComponents;

	enum
	{
		MODE_TITLE,
		MODE_LOCAL_MAP,
		MODE_HELP,
		MODE_GAME_OVER,
		MODE_WINNER,
		MODE_PAUSE
	};

	int GameMode;



protected:

	//game components
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;

	bool UpdateTitleScreen(float fElapsedTime);
	bool UpdateMapScreen(float fElapsedTime);
	bool UpdateHelpScreen(float fElapsedTime);
	bool UpdateGameOverScreen(float fElapsedTime);
	bool UpdateWinnerScreen(float fElapsedTime);
	bool UpdatePauseScreen(float fElapsedTime);


	//utils
	void HandleInput(float fElapsedTime);
	void CheckCollisionsVsColectables(float& px, float& py);
	void CheckCollisionsVsStaticObjects(Entity* creature, float& px, float& py);
	void CheckAttacksVsEnemies(Entity* creature, float& px, float& py);
	void CheckCollisionsVsDoor(float& px, float& py);


	void DrawBigText(string sText, int x, int y);
	void DisplayDialog(vector<string> vecText, int x, int y);

	void SaveGame();
	void LoadGame();



public:

	static Maze_game* get_instance();

	friend Camera_view;

	void Damage(Sword* sword, Creature* victim);

};

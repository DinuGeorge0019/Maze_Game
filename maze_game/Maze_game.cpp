#include "Maze_game.h"

//singleton design pattern initialization
Maze_game* Maze_game::game_instace = nullptr;
Maze_game* Maze_game::get_instance()
{
	if (game_instace == nullptr)
	{
		game_instace = new Maze_game;
	}
	return game_instace;
}


Maze_game::Maze_game()
{
	m_sAppName = L"MAZE GAME";
	GameMode = MODE_TITLE;
	level = nullptr;
	player = nullptr;
	spriteFont = nullptr;
	spriteMap = nullptr;
	striteComponents = nullptr;
}


//GAME
bool Maze_game::OnUserCreate()
{

	player = new Player;

	creatures.push_back(player);

	level = new Level1_map(creatures);
	spriteMap = new olcSprite(L"Sprites/map_components.spr");
	spriteFont = new olcSprite(L"Sprites/letters.spr");
	striteComponents = new olcSprite(L"Sprites/door_and_others.spr");

	return true;
}


//Utility functions

void Maze_game::DrawBigText(string sText, int x, int y)
{
	int i = 0;
	for (auto c : sText)
	{
		int sx = ((c - 32) % 16) * 8;
		int sy = ((c - 32) / 16) * 8;
		DrawPartialSprite(x + i * 8, y, spriteFont, sx, sy, 8, 8);
		i++;
	}

}

void Maze_game::DisplayDialog(vector<string> vecText, int x, int y)
{
	int nMaxLineLength = 0;
	int nLines = vecText.size();

	for (auto l : vecText)	if (l.size() > nMaxLineLength) nMaxLineLength = l.size();

	// Draw Box
	Fill(x - 1, y - 1, x + nMaxLineLength * 8 + 1, y + nLines * 8 + 1, PIXEL_SOLID, FG_DARK_BLUE);
	DrawLine(x - 2, y - 2, x - 2, y + nLines * 8 + 1);
	DrawLine(x + nMaxLineLength * 8 + 1, y - 2, x + nMaxLineLength * 8 + 1, y + nLines * 8 + 1);
	DrawLine(x - 2, y - 2, x + nMaxLineLength * 8 + 1, y - 2);
	DrawLine(x - 2, y + nLines * 8 + 1, x + nMaxLineLength * 8 + 1, y + nLines * 8 + 1);

	for (int l = 0; l < vecText.size(); l++)
		DrawBigText(vecText[l], x, y + l * 8);
}



void Maze_game::CheckCollisionsVsColectables(float& px, float& py)
{

	//Colectables
	if (level->GetTile(px + 0.0f, py + 0.0f) == L'o')
	{
		level->SetTile(px + 0.0f, py + 0.0f, L'.');
		player->Gold += rand() % (10 - 1) + 1;
	}
	 
	if (level->GetTile(px + 0.0f, py + 1.0f) == L'o')
	{
		level->SetTile(px + 0.0f, py + 1.0f, L'.');
		player->Gold += rand() % (10 - 1) + 1;
	}

	if (level->GetTile(px + 1.0f, py + 0.0f) == L'o')
	{
		level->SetTile(px + 1.0f, py + 0.0f, L'.');
		player->Gold += rand() % (10 - 1) + 1;
	}
		
	if (level->GetTile(px + 1.0f, py + 1.0f) == L'o')
	{
		level->SetTile(px + 1.0f, py + 1.0f, L'.');
		player->Gold += rand() % (10 - 1) + 1;
	}
		
}

void Maze_game::CheckCollisionsVsDoor(float& px, float& py)
{



	if (level->GetTile(px + 0.0f, py + 0.0f) == L'D' && player->noKeys > 0)
	{
		level->SetTile(px + 0.0f, py + 0.0f, L'.');
		player->noKeys--;
	}
	else if (level->GetTile(px + 0.0f, py + 0.0f) == L'E')
	{
		GameMode = MODE_WINNER;
	}

	if (level->GetTile(px + 0.0f, py + 1.0f) == L'D' && player->noKeys > 0)
	{
		level->SetTile(px + 0.0f, py + 1.0f, L'.');
		player->noKeys--;
	}
	else if (level->GetTile(px + 0.0f, py + 1.0f) == L'E')
	{
		GameMode = MODE_WINNER;
	}

	if (level->GetTile(px + 1.0f, py + 0.0f) == L'D' && player->noKeys > 0)
	{
		level->SetTile(px + 1.0f, py + 0.0f, L'.');
		player->noKeys--;
	}
	else if (level->GetTile(px + 1.0f, py + 0.0f) == L'E')
	{
		GameMode = MODE_WINNER;
	}

		
	if (level->GetTile(px + 1.0f, py + 1.0f) == L'D' && player->noKeys > 0)
	{
		level->SetTile(px + 1.0f, py + 1.0f, L'.');
		player->noKeys--;
	}
	else if (level->GetTile(px + 1.0f, py + 1.0f) == L'E')
	{
		GameMode = MODE_WINNER;
	}

		
}

void Maze_game::CheckCollisionsVsStaticObjects(Entity* creature, float& px, float& py)
{
	if (creature->Vx <= 0) // Moving Left
	{

		if (level->GetSolid(px + 0.0f, creature->Py + 0.0f) || level->GetSolid(px + 0.0f, creature->Py + 0.8f) ) // top left - bot left
		{
			px = (int)px + 1;
			creature->Vx = 0;
		}

	}
	else // Moving Right
	{
		if (level->GetSolid(px + 1.0f, creature->Py + 0.0f) || level->GetSolid(px + 1.0f, creature->Py + 0.8f)) // top right - bot right
		{

			px = (int)px;
			creature->Vx = 0;

		}
	}

	if (creature->Vy <= 0) // Moving up
	{
		if (level->GetSolid(px + 0.0f, py + 0.0f) || level->GetSolid(px + 0.8f, py + 0.0f) ) // top left - top right
		{
			py = (int)py + 1;
			creature->Vy = 0;
		}
	}
	else // Moving down
	{
		if (level->GetSolid(px + 0.0f, py + 1.0f) || level->GetSolid(px + 0.8f, py + 1.0f) ) // bot left - bot right
		{
			py = (int)py;
			creature->Vy = 0;
		}
	}
}

void Maze_game::CheckAttacksVsEnemies(Entity* object, float& px, float& py)
{
	for (auto& dinamic_obj : hits)
	{
		if (px < (dinamic_obj->Px + 1.0f) && (px + 1.0f) > dinamic_obj->Px &&
			py < (dinamic_obj->Py + 1.0f) && (py + 1.0f) > dinamic_obj->Py)
		{		
			// Dynamic object is a creature
			Damage((Sword*)dinamic_obj, (Creature*)object);
		}
	}
}

void Maze_game::HandleInput(float fElapsedTime)
{
	if (IsFocused())
	{
		if (GetKey(VK_UP).bHeld)
		{
			player->Vy = -6.0f;
		}

		if (GetKey(VK_DOWN).bHeld)
		{
			player->Vy = 6.0f;
		}

		if (GetKey(VK_LEFT).bHeld)
		{
			player->Vx = -6.0f;
		}

		if (GetKey(VK_RIGHT).bHeld)
		{
			player->Vx = 6.0f;
		}

		if (GetKey(L'H').bReleased)
			GameMode = MODE_HELP;

		if (GetKey(L'P').bReleased)
			GameMode = MODE_PAUSE;


		if (GetKey(VK_SPACE).bReleased) // Interaction requested
		{

			// Grab a point from the direction the player is facing and check for interactions										
			float targetPx, targetPy;

			if (player->GetFacingDirection() == 0) // South
			{
				targetPx = player->Px + 0.5f;
				targetPy = player->Py + 1.5f;
			}

			if (player->GetFacingDirection() == 1) // West
			{
				targetPx = player->Px - 0.5f;
				targetPy = player->Py + 0.5f;
			}

			if (player->GetFacingDirection() == 2) // North
			{
				targetPx = player->Px + 0.5f;
				targetPy = player->Py - 0.5f;
			}

			if (player->GetFacingDirection() == 3) // East
			{
				targetPx = player->Px + 1.5f;
				targetPy = player->Py + 0.5f;
			}

			// Check if test point has hit a dynamic object
			bool hit_something = false;
			for (auto creature : creatures)
			{
				if (targetPx > creature->Px  && targetPx < (creature->Px + 1.0f) && targetPy > creature->Py && targetPy < (creature->Py + 1.0f))
				{
					if (creature->friendly == true)
					{
						hit_something = true;

						creature->OnInteract(player);
					}
					else
					{
						player->PerformAttack(hits);
					}
				}
			}

			if (!hit_something) // Default action is attack
			{
				player->PerformAttack(hits);
			}

		}

	}


	for (auto& creature : creatures)
	{

		//Get player new positions 
		float newCreaturePosX = creature->Px + creature->Vx * fElapsedTime;
		float newCreaturePosY = creature->Py + creature->Vy * fElapsedTime;

		//check for colectables items
		if (creature == player)
			CheckCollisionsVsColectables(newCreaturePosX, newCreaturePosY);

		//check for doors
		if (creature == player)
			CheckCollisionsVsDoor(newCreaturePosX, newCreaturePosY);

		// Check for Collision
		CheckCollisionsVsStaticObjects(creature, newCreaturePosX, newCreaturePosY);

		// hit enemies 
		if(creature != player)
			CheckAttacksVsEnemies(creature, newCreaturePosX, newCreaturePosY);

		//Apply new pos 
		creature->Px = newCreaturePosX;
		creature->Py = newCreaturePosY;

		creature->Update(fElapsedTime, player);

	}

	
}

bool Maze_game::OnUserUpdate(float fElapsedTime)
{

	switch (GameMode)
	{
	case MODE_TITLE:
		return UpdateTitleScreen(fElapsedTime);
	case MODE_LOCAL_MAP:
		return UpdateMapScreen(fElapsedTime);
	case MODE_HELP:
		return UpdateHelpScreen(fElapsedTime);
	case MODE_GAME_OVER:
		return UpdateGameOverScreen(fElapsedTime);
	case MODE_WINNER:
		return UpdateWinnerScreen(fElapsedTime);	
	case MODE_PAUSE:
		return UpdatePauseScreen(fElapsedTime);
	}


}

void Maze_game::SaveGame()
{
	wfstream out_file;


	out_file.open("level1_save_creatures.txt", ios::out | ios::trunc);
	//player data
	out_file << player->Px << endl;
	out_file << player->Py << endl;
	out_file << player->nHealth << endl;
	out_file << player->Gold << endl;
	out_file << player->noKeys << endl;

	//creatures data
	for (int i = 1; i < creatures.size(); i++)
	{
		out_file << creatures[i]->friendly << endl;
		out_file << creatures[i]->Px << endl;
		out_file << creatures[i]->Py << endl;
	}

	out_file.close();


	out_file.open("level1_save_map.txt", ios::out | ios::trunc);

	out_file << level->nWidth << endl;
	out_file << level->nHeight << endl;
	for (int i = 0; i < level->nHeight; i++)
	{
		for (int j = 0; j < level->nWidth; j++)
		{
			out_file << level->GetTile(j, i);
		}
		out_file << endl;
	}

	out_file.close();
}

void Maze_game::LoadGame()
{

	wfstream in_file;
	in_file.open("level1_save_creatures.txt", ios::in);

	//player data
	in_file >> player->Px;
	in_file >> player->Py;
	in_file >> player->nHealth;
	in_file >> player->Gold;
	in_file >> player->noKeys;

	creatures.clear();
	creatures.push_back(player);

	//enemies data

	bool temp_state;
	while (in_file >> temp_state)
	{

		if (temp_state == true)
		{
			Friend* new_friend = new Friend;
			in_file >> new_friend->Px;
			in_file >> new_friend->Py;
			creatures.push_back(new_friend);
		}
		else if (temp_state == false)
		{
			Enemy* new_enemy = new Enemy;
			in_file >> new_enemy->Px;
			in_file >> new_enemy->Py;
			creatures.push_back(new_enemy);
		}


	}
	in_file.close();


	in_file.open("level1_save_map.txt", ios::in);

	in_file >> level->nWidth;
	in_file >> level->nHeight;


	level->setLevelToNULL();

	wstring bigString = L"";

	wstring sLevel_temp;
	while (getline(in_file, sLevel_temp))
	{
		bigString += sLevel_temp;
	}

	level->setLevelToGivenString(bigString);

	in_file.close();
}

bool Maze_game::UpdateTitleScreen(float fElapsedTime)
{

	Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

	DrawBigText("ESCAPE DEATH", 40, 30);
	DrawBigText("SIMULATOR", 50, 40);
	DrawBigText("Press ENTER to start", 0, 80);
	DrawBigText("Press L to load last save", 0, 90);


	if (GetKey(VK_RETURN).bReleased)
	{
		GameMode = MODE_LOCAL_MAP;
	}

	if (GetKey(L'L').bReleased)
	{
		LoadGame();
		GameMode = MODE_LOCAL_MAP;
	}
		

	return true;
}

bool Maze_game::UpdateGameOverScreen(float fElapsedTime)
{

	Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');


	DrawBigText("GAME OVER", 40, 30);
	DrawBigText("Press ENTER", 0, 70);
	DrawBigText("to play again", 0, 80);
	DrawBigText("Press Q to quit", 0, 90);

	if (GetKey(VK_RETURN).bReleased)
	{
		delete player;
		player = new Player;
		creatures.clear();
		creatures.push_back(player);
		delete level;
		level = new Level1_map(creatures);

		GameMode = MODE_TITLE;
	}

	if (GetKey(L'Q').bReleased)
		return false;

	return true;
}

bool Maze_game::UpdateWinnerScreen(float fElapsedTime)
{
	Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');
	DrawBigText("WINNER", 60, 10);

	string sHealth = "HP: " + to_string(player->nHealth) + "/" + to_string(player->nHealthMax);
	string sKeys = "Keys: " + to_string(player->noKeys);
	string sGold = "Gold: " + to_string(player->Gold);

	DrawBigText(sHealth, 0, 40);
	DrawBigText(sGold, 0, 50);
	DrawBigText(sKeys, 0, 60);


	DrawBigText("Press ENTER", 0, 70);
	DrawBigText("to play again", 0, 80);
	DrawBigText("Press Q to quit", 0, 90);

	if (GetKey(VK_RETURN).bReleased)
	{
		delete player;
		player = new Player;
		creatures.clear();
		creatures.push_back(player);
		delete level;
		level = new Level1_map(creatures);

		GameMode = MODE_TITLE;
	}

	if (GetKey(L'Q').bReleased)
		return false;

	return true;
}

bool Maze_game::UpdatePauseScreen(float fElapsedTime)
{

	Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');

	DrawBigText("PAUSED", 60, 30);
	DrawBigText("Press ENTER to start", 4, 60);
	DrawBigText("Press S to save", 4, 70);
	DrawBigText("Press Q to quit", 4, 80);

	if (GetKey(VK_RETURN).bReleased)
	{
		GameMode = MODE_LOCAL_MAP;
	}

	if (GetKey(L'Q').bReleased)
	{
		return false;
	}

	if (GetKey(L'S').bReleased)
	{
		SaveGame();
	}


	return true;
}

bool Maze_game::UpdateHelpScreen(float fElapsedTime)
{

	Fill(0, 0, ScreenWidth(), ScreenHeight(), L' ');
	DrawBigText("HELP", 4, 4);
	DrawBigText("Up arrow = walk NORTH", 4, 20);
	DrawBigText("Down arrow = walk SOUTH", 4, 30);
	DrawBigText("Left arrow = walk WEST", 4, 40);
	DrawBigText("Right arrow = walk EAST", 4, 50);
	DrawBigText("Space = attack", 4, 60);
	DrawBigText("H = exit/enter help", 4, 70);

	//if (GetKey(VK_ESCAPE).bReleased)
		//return false;


	if (GetKey(L'H').bReleased)
		GameMode = MODE_LOCAL_MAP;


	return true;
}

bool Maze_game::UpdateMapScreen(float fElapsedTime)
{
	if (player->nHealth <= 0)
	{
		GameMode = MODE_GAME_OVER;
	}

	player->Vx = 0;
	player->Vy = 0;

	HandleInput(fElapsedTime);

	// if a creature's health is below 0 then erase it 
	creatures.erase(remove_if(creatures.begin(), creatures.end(), [&](const Entity* creature) {return ((Creature*)creature)->nHealth <= 0 || ((Creature*)creature)->isDead || ((Creature*)creature)->isRedundant;; }), creatures.end());


	//update hits
	for (auto& hit : hits)
	{
		hit->Update(fElapsedTime, player);
	}

	// remove redundant hits
	hits.erase( remove_if(hits.begin(), hits.end(), [&](const Entity* hit) {return ((Sword*)hit)->isRedundant; }), hits.end());



	// Link camera to player position
	camera_view.PosX = player->Px;
	camera_view.PosY = player->Py;

	// Draw Level

	int nVisibleTilesX = ScreenWidth() / tile_data.nWidth;
	int nVisibleTilesY = ScreenHeight() / tile_data.nHeight;


	//Offset of camera | top-left most visible tile
	camera_view.fOffsetX = camera_view.PosX - nVisibleTilesX / 2.0f;
	camera_view.fOffsetY = camera_view.PosY - nVisibleTilesY / 2.0f;

	// Make camera see a whole screen all the time
	camera_view.ClampCamera(level->nWidth, level->nHeight, nVisibleTilesX, nVisibleTilesY);


	// Get offset of tiles for smooth movement of camera
	float fTileOffsetX = (camera_view.fOffsetX - (int)camera_view.fOffsetX) * tile_data.nWidth;
	float fTileOffsetY = (camera_view.fOffsetY - (int)camera_view.fOffsetY) * tile_data.nHeight;


	// Draw visible tile map
	Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_CYAN);

	for (int x = -1; x <= nVisibleTilesX + 1; x++)
	{
		for (int y = -1; y <= nVisibleTilesY + 1; y++)
		{
			wchar_t sTileID = level->GetTile( x + camera_view.fOffsetX, y + camera_view.fOffsetY);
			switch (sTileID)
			{
			case L'.': // Sky
			{
				Fill(x * tile_data.nWidth - fTileOffsetX, y * tile_data.nHeight - fTileOffsetY, (x + 1) * tile_data.nWidth - fTileOffsetX, (y + 1) * tile_data.nHeight - fTileOffsetY, PIXEL_SOLID, FG_CYAN);
				break;
			}
			case L'#': // Solid Block
			{
				DrawPartialSprite(x * tile_data.nWidth - fTileOffsetX, y * tile_data.nHeight - fTileOffsetY, spriteMap, 2 * tile_data.nWidth, 0 * tile_data.nHeight, tile_data.nWidth, tile_data.nHeight);
				break;
			}
			case L'o': // Coin
			{
				DrawPartialSprite(x * tile_data.nWidth - fTileOffsetX, y * tile_data.nHeight - fTileOffsetY, spriteMap, 3 * tile_data.nWidth, 0 * tile_data.nHeight, tile_data.nWidth, tile_data.nHeight);
				break;
			}
			case L'D'://door
			{
				//Fill(x * tile_data.nWidth - fTileOffsetX, y * tile_data.nHeight - fTileOffsetY, (x + 1) * tile_data.nWidth - fTileOffsetX, (y + 1) * tile_data.nHeight - fTileOffsetY, PIXEL_SOLID, FG_Olive);
				DrawPartialSprite(x * tile_data.nWidth - fTileOffsetX, y * tile_data.nHeight - fTileOffsetY, striteComponents, 7 * tile_data.nWidth, 2 * tile_data.nHeight, tile_data.nWidth, tile_data.nHeight);
				break;
			}

			case L'G': //Ground
			{
				DrawPartialSprite(x * tile_data.nWidth - fTileOffsetX, y * tile_data.nHeight - fTileOffsetY, striteComponents, 4 * tile_data.nWidth, 1 * tile_data.nHeight, tile_data.nWidth, tile_data.nHeight);
				break;
			}

			case L'E': //Exit
			{
				DrawPartialSprite(x * tile_data.nWidth - fTileOffsetX, y * tile_data.nHeight - fTileOffsetY, striteComponents, 5 * tile_data.nWidth, 1 * tile_data.nHeight, tile_data.nWidth, tile_data.nHeight);
				break;
			}

			default:
				DrawPartialSprite(x * tile_data.nWidth - fTileOffsetX, y * tile_data.nHeight - fTileOffsetY, striteComponents, 4 * tile_data.nWidth, 1 * tile_data.nHeight, tile_data.nWidth, tile_data.nHeight);
				break;
			}
		}
	}

	//Draw Creatures


	for (int i = 1; i < creatures.size(); i++)
	{
		creatures[i]->DrawSelf(this, camera_view.fOffsetX, camera_view.fOffsetY);
	}
		
	player->DrawSelf(this, camera_view.fOffsetX, camera_view.fOffsetY);

	for(auto& hit : hits)
		hit->DrawSelf(this,camera_view.fOffsetX, camera_view.fOffsetY);


	string sHealth = "HP: " + to_string(player->nHealth) + "/" + to_string(player->nHealthMax);
	string sKeys = "Keys: " + to_string(player->noKeys);
	string sGold = "Gold: " + to_string(player->Gold);
	DisplayDialog({ sHealth , sKeys, sGold }, 120, 5);


	return true;
}




void Maze_game::Damage(Sword* sword, Creature* victim)
{
	// Attack victim with damage
	victim->nHealth -= sword->damage;
	sword->isRedundant = true;

}

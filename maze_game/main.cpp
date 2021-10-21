#include "Maze_game.h"

int main()
{

	Maze_game* game = game->get_instance();
	if(game->ConstructConsole(200, 100, 7, 7))
		game->Start();

	return 0;
}
#include "Game.h"

int main()
{
	Game* game = new Game("Triangles", 800, 600);

	while (game->isRunning())
	{
		game->handleEvents();
		game->render();
	}
	
	delete game;
}
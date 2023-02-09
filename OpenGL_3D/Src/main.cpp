#include "Game.h"

int main()
{
	auto game = std::make_unique<Game>("Cubes", 800, 600);
	
	while (game->isRunning())
	{
		game->handleEvents();
		game->render();
	}
}
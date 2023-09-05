#include "game.h"

int main()
{
	std::unique_ptr<Game>game_ptr = std::make_unique<Game>();
	game_ptr->run();
	return 0;
}
#include "game.h"

void Game::display()
{
	if (isPlaying)
	{
		window.draw(background_s);
	}
	else
	{
		window.draw(splashScreenText);
	}

	window.display();
	window.clear();
}
#include "game.h"

void Game::display()
{
	if (isPlaying)
	{
		window.draw(background_s);
		window.draw(player_sprite->getSprite());
	}

	else
	{
		window.draw(splashScreenText);
	}

	window.display();
	window.clear();
}
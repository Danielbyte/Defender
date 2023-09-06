#include "game.h"

void Game::display()
{
	if (isPlaying)
	{
		window.draw(background_s);
		window.draw(sprite_store->getPlayerShipSprite());
	}

	else
	{
		window.draw(splashScreenText);
	}

	window.display();
	window.clear();
}
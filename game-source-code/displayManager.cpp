#include "game.h"

void Game::display()
{
	if (isPlaying)
	{
		window.draw(background_s);
		window.draw(player_sprite->getSprite());
		for (auto& laser : laser_sprite)
		{
			window.draw(laser->getSprite());
		}

		for (auto& _lander : lander_object_sprites)
		{
			window.draw(_lander->getSprite());
		}

		for (auto& lander_missile : lander_missile_sprites)
		{
			window.draw(lander_missile->getSprite());
		}

		for (auto& humanoid : humanoid_sprites)
		{
			window.draw(humanoid->getSprite());
		}
	}

	else
	{
		window.draw(splashScreenText);
	}

	window.display();
	window.clear();
}
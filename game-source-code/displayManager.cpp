#include "game.h"

void Game::display(const float dt)
{
	if (isPlaying)
	{
		updateCamera(dt);
		updateBackgroundView();
		window.setView(gameView);
		window.draw(background_s);
		window.draw(background_s2);
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

void Game::updateCamera(const float dt)
{
	const float scrollSpeed = 10.0f;
	auto [playerXpos, playerYpos] = player_obj->getPlayerPosition();
	viewCenter.x = playerXpos + (viewCenter.x - playerXpos) * scrollSpeed * dt;
	gameView.setCenter(viewCenter);
}

void Game::updateBackgroundView()
{
	auto [playerXpos, playerYpos] = player_obj->getPlayerPosition();
	auto backgroundWidth = 1200.0f;

	auto distance1 = abs(playerXpos - background1Position.x);
	auto distance2 = abs(playerXpos - background2Position.x);
	auto playerDirection = player_obj->getDirection();

	if (distance2 > distance1)
	{
		if (playerDirection == "right")
		{
			if (playerXpos >= background1Position.x)
				background2Position.x = background1Position.x + backgroundWidth;

			background_s2.setPosition(background2Position);
			return;
		}
		background2Position.x = background1Position.x - backgroundWidth;
		background_s2.setPosition(background2Position);
		return;
	}

	if (distance1 > distance2)
	{
		if (playerDirection == "right")
		{
			if (playerXpos >= background2Position.x)
				background1Position.x = background2Position.x + backgroundWidth;

			background_s.setPosition(background1Position);
			return;
		}
		background1Position.x = background2Position.x - backgroundWidth;
		background_s.setPosition(background1Position);
	}
}
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
		window.draw(landscape1_sprite->getSprite());
		window.draw(landscape2_sprite->getSprite());
		window.draw(viewDivider_s);
		window.draw(miniManpBorders_s);
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
	viewDivider_s.setPosition(playerXpos, 100.0f);
	miniManpBorders_s.setPosition(playerXpos, 50.0f);
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
			landscape2->updateTerrain(landscape2_sprite, background2Position.x);
			return;
		}
		
		if (playerXpos <= background1Position.x)
			background2Position.x = background1Position.x - backgroundWidth;

		landscape2->updateTerrain(landscape2_sprite, background2Position.x);
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
			landscape1->updateTerrain(landscape1_sprite, background1Position.x);
			return;
		}
		
		if (playerXpos <= background2Position.x)
			background1Position.x = background2Position.x - backgroundWidth;

		landscape1->updateTerrain(landscape1_sprite, background1Position.x);
		background_s.setPosition(background1Position);
	}
}
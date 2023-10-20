#include "game.h"

void Game::display(const float dt)
{
	if (gameOver)
	{
		viewCenter.x = 400.0f;
		viewCenter.y = windowHeight / 2.0f;
		gameView.setCenter(viewCenter);
		window->setView(gameView);
		window->draw(endOfGame);
		window->display();
		window->clear();
		return;
	}

	if (playerWon)
	{
		viewCenter.x = 400.0f;
		viewCenter.y = windowHeight / 2.0f;
		gameView.setCenter(viewCenter);
		window->setView(gameView);
		window->draw(winText);
		window->display();
		window->clear();
		return;
	}

	if (isPlaying)
	{
		updateCamera();
		minimap->update(player_obj);
		updateBackgroundView();
		window->clear();
		window->setView(gameView);
		window->draw(background_s);
		window->draw(background_s2);
		window->draw(landscape1_sprite->getSprite());
		window->draw(landscape2_sprite->getSprite());
		window->draw(miniMapSection_s);
		window->draw(highScore);
		window->draw(currentScore);
		for (auto& laser : laser_sprite)
		{
			window->draw(laser->getSprite());
		}

		auto lander = lander_objects.begin();
		for (auto& _lander : lander_object_sprites)
		{
			if ((*lander)->getIfTeleporting())
				window->draw(_lander->getAnimationSprite());

			if (!(*lander)->getIfTeleporting())
				window->draw(_lander->getSprite());

			++lander;
		}

		for (auto& lander_missile : lander_missile_sprites)
		{
			window->draw(lander_missile->getSprite());
		}

		for (auto& humanoid : humanoid_sprites)
		{
			window->draw(humanoid->getSprite());
		}

		for (auto& bomber : bomber_sprites)
		{
			window->draw(bomber->getSprite());
		}

		for (auto& mine : mine_sprites)
		{
			window->draw(mine->getSprite());
		}

		PlayerState playerState = player_obj->getPlayerState();

		if (playerState == PlayerState::Alive)
			window->draw(player_sprite->getSprite());

		if (playerState == PlayerState::Dead)
			window->draw(player_sprite->getAnimationSprite());

		minimap->drawMiniMap(window, player_sprite, lander_object_sprites, humanoid_sprites, bomber_sprites);
	}

	else
	{
		window->draw(splashScreenText);
	}

	window->display();
	window->clear();
}

void Game::updateCamera()
{
	auto [playerXpos, playerYpos] = player_obj->getPlayerPosition();
	viewCenter.x = playerXpos;
	gameView.setCenter(viewCenter);
	miniMapSection_s.setPosition(viewCenter.x, 51.0f);
}

void Game::updateBackgroundView()
{
	auto [playerXpos, playerYpos] = player_obj->getPlayerPosition();
	auto backgroundWidth = 3200.0f;

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
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
		//updateBackgroundView();
		window->clear();
		window->setView(gameView);
		window->draw(background_s);
		//window->draw(landscape1_sprite->getSprite());
		//window->draw(landscape2_sprite->getSprite());
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
			auto [isShot, isExploding] = (*lander)->getLanderStatus();

			if ((*lander)->getIfTeleporting() && !isShot)
				window->draw(_lander->getAnimationSprite());

			if (!(*lander)->getIfTeleporting() && !isShot)
				window->draw(_lander->getSprite());

			if (isExploding)
				window->draw(_lander->getExplosionSprite());

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
	//Should Probably do more interesting things
}
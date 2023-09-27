#include "playerSprite.h"

PlayerSprite::PlayerSprite()
{
	sf::Vector2f dimensions;
	dimensions.x = 50.0f;
	dimensions.y = 20.0f;
	loadTextures();
	InitialiseEntityOrigin(dimensions);
}

void PlayerSprite::loadTextures()
{
	player_tR.loadFromFile("resources/spaceship-right.png");
	player_tL.loadFromFile("resources/spaceship-left.png");
	player_death_tR.loadFromFile("resources/spaceship-right-death.png");
	player_death_TL.loadFromFile("resources/spaceship-left-death.png");
}

void PlayerSprite::setTexture(std::string playerState, bool& gameOver, StopWatch& animation_watch)
{
	auto left = getIfLeft();
	auto right = getIfRight();

	if (playerState == "dead")
	{
		if (left)
		{
			updateSpriteTexture(player_death_TL);

			if ((animation_watch.time_elapsed() >= 0.5f))
				gameOver = true;

			return;
		}

		updateSpriteTexture(player_death_tR);
		
		if ((animation_watch.time_elapsed() >= 0.5f))
			gameOver = true;

		return;
	}

	if (right)
	{
		updateSpriteTexture(player_tR);
	}

	if (left)
	{
		updateSpriteTexture(player_tL);
	}
}
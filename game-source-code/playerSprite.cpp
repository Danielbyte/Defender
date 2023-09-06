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
}

void PlayerSprite::setTexture()
{
	auto left = getIfLeft();
	auto right = getIfRight();

	if (right)
	{
		updateSpriteTexture(player_tR);
	}

	if (left)
	{
		updateSpriteTexture(player_tL);
	}
}
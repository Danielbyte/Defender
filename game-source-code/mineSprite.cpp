#include "mineSprite.h"

MineSprite::MineSprite():
	period{0.1f}
{
	sf::Vector2f dimensions;
	sf::Vector2f NA;
	dimensions.x = 8.0f;
	dimensions.y = 8.0f;
	loadTextures();
	InitialiseEntityOrigin(dimensions, NA, NA);

	animation_watch->restart();
}

void MineSprite::loadTextures()
{
	mine1_t.loadFromFile("resources/mine1.png");
	mine2_t.loadFromFile("resources/mine2.png");
}

void MineSprite::setTexture()
{
	auto time = animation_watch->time_elapsed();
	if (time >= 0.0f && time <= period)
	{
		updateSpriteTexture(mine1_t, mini_t);
	}

	if (time > period && time <= 2 * period)
	{
		updateSpriteTexture(mine2_t, mini_t);
		animation_watch->restart();
	}
}
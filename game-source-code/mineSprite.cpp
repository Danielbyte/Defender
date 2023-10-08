#include "mineSprite.h"

MineSprite::MineSprite()
{
	sf::Vector2f dimensions;
	sf::Vector2f miniDimensions;
	sf::Vector2f NA;
	dimensions.x = 50.0f;
	dimensions.y = 20.0f;
	miniDimensions.x = 27.0f;
	miniDimensions.y = 10.0f;
	loadTextures();
	InitialiseEntityOrigin(dimensions, miniDimensions, NA);

	animation_watch->restart();
}

void MineSprite::loadTextures()
{
	mine1_t.loadFromFile("resources/mine1.png");
	mine2_t.loadFromFile("resources/mine2.png");
}
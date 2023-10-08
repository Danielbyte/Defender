#include "bomberSprite.h"

BomberSprite::BomberSprite():
	period{0.1f}
{
	sf::Vector2f dimensions;
	sf::Vector2f miniDimensions;
	sf::Vector2f NA;
	dimensions.x = 20.0f;
	dimensions.y = 20.0f;
	miniDimensions.x = 13.0f;
	miniDimensions.y = 5.0f;

	loadTextures();
	InitialiseEntityOrigin(dimensions, miniDimensions, NA);
	loadTextures();
	animation_watch->restart();
}

void BomberSprite::loadTextures()
{
	bomber1_t.loadFromFile("resources/bomber1.png");
	bomber2_t.loadFromFile("resources/bomber2.png");
	bomber3_t.loadFromFile("resources/bomber3.png");
	bomber4_t.loadFromFile("resources/bomber4.png");
	bomber5_t.loadFromFile("resources/bomber5.png");
	bomber6_t.loadFromFile("resources/bomber6.png");
	bomber7_t.loadFromFile("resources/bomber7.png");
}

void BomberSprite::setTexture()
{
	auto time = animation_watch->time_elapsed();

	if (time >= 0.0f && time <= period)
	{

	}

	if (time > period && time <= 2 * period)
	{

	}

	if (time > 2 * period && time <= 3 * period)
	{

	}

	if (time > 3 * period && time <= 4 * period)
	{

	}

	if (time > 4 * period && time <= 5 * period)
	{

	}

	if (time > 5 * period && time <= 6 * period)
	{

	}

	if (time > 6 * period && time <= 7 * period)
	{

	}
}
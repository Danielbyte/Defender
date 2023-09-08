#include "landerSprite.h"

LanderSprite::LanderSprite():
	sprite_period{0.3f} //display each sprite for 0.5 sec
{
	sf::Vector2f dimensions;
	dimensions.x = 16.0f;
	dimensions.y = 16.0f;
	loadTextures();
	InitialiseEntityOrigin(dimensions);
}

void LanderSprite::setTexture(std::shared_ptr<StopWatch>& watch)
{
	auto _time = watch->time_elapsed();
	if (_time >= 0 && _time <= sprite_period)
	{
		updateSpriteTexture(lander1_t);
		return;
	}

	if (_time > sprite_period && _time <= 2 * sprite_period)
	{
		updateSpriteTexture(lander2_t);
		return;
	}

	if (_time > 2 * sprite_period && _time <= 3 * sprite_period)
	{
		updateSpriteTexture(lander3_t);
		return;
	}

	if (_time > 3 * sprite_period && _time <= 4 * sprite_period)
	{
		updateSpriteTexture(lander4_t);
		watch->restart();
	}
}

void LanderSprite::loadTextures()
{
	lander1_t.loadFromFile("resources/lander1.png");
	lander2_t.loadFromFile("resources/lander2.png");
	lander3_t.loadFromFile("resources/lander3.png");
	lander4_t.loadFromFile("resources/lander4.png");
}
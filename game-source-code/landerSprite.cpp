#include "landerSprite.h"

LanderSprite::LanderSprite():
	sprite_period{0.3f} //display each sprite for 0.5 sec
{
	sf::Vector2f dimensions;
	dimensions.x = 16.0f;
	dimensions.y = 16.0f;
	sf::Vector2f miniDimensions;
	loadTextures();
	InitialiseEntityOrigin(dimensions, miniDimensions);
}

void LanderSprite::setTexture(std::shared_ptr<StopWatch>& watch, const bool isTeleporting)
{
	auto _time = watch->time_elapsed();

	if (isTeleporting)
	{
		auto period = 0.1;
		if (_time >= 0.0f && _time <= period)
		{

		}

		if (_time >= 0.0f && _time <= 2 * period)
		{

		}

		if (_time >= 2 * period && _time <= 3 * period)
		{

		}

		if (_time >= 3 * period && _time <= 4 * period)
		{

		}

		if (_time >= 4 * period && _time <= 5 * period)
		{

		}

		if (_time >= 5 * period && _time <= 6 * period)
		{

		}

		if (_time >= 6 * period && _time <= 7 * period)
		{

		}

		return;
	}

	if (_time >= 0 && _time <= sprite_period)
	{
		updateSpriteTexture(lander1_t, miniMap_t);
		return;
	}

	if (_time > sprite_period && _time <= 2 * sprite_period)
	{
		updateSpriteTexture(lander2_t, miniMap_t);
		return;
	}

	if (_time > 2 * sprite_period && _time <= 3 * sprite_period)
	{
		updateSpriteTexture(lander3_t, miniMap_t);
		return;
	}

	if (_time > 3 * sprite_period && _time <= 4 * sprite_period)
	{
		updateSpriteTexture(lander4_t, miniMap_t);
		watch->restart();
	}
}

void LanderSprite::loadTextures()
{
	landerTeleport1_t.loadFromFile("resources/lander-teleport-1.png");
	landerTeleport1_t.loadFromFile("resources/lander-teleport-2.png");
	landerTeleport1_t.loadFromFile("resources/lander-teleport-3.png");
	landerTeleport1_t.loadFromFile("resources/lander-teleport-4.png");
	landerTeleport1_t.loadFromFile("resources/lander-teleport-5.png");
	landerTeleport1_t.loadFromFile("resources/lander-teleport-6.png");
	landerTeleport1_t.loadFromFile("resources/lander-teleport-7.png");
	lander1_t.loadFromFile("resources/lander1.png");
	lander2_t.loadFromFile("resources/lander2.png");
	lander3_t.loadFromFile("resources/lander3.png");
	lander4_t.loadFromFile("resources/lander4.png");
	miniMap_t.loadFromFile("resources/mini-lander.png");
}
#include "landerSprite.h"

LanderSprite::LanderSprite():
	sprite_period{0.03f} //display each sprite for 0.5 sec
{
	sf::Vector2f mainDimensions;
	mainDimensions.x = 40.0f;
	mainDimensions.y = 40.0f;

	sf::Vector2f miniDimensions;
	miniDimensions.x = 13.0f;
	miniDimensions.y = 5.0f;

	sf::Vector2f teleportDimensions;
	teleportDimensions.x = 118.0f;
	teleportDimensions.y = 200.0f;

	loadTextures();
	InitialiseEntityOrigin(mainDimensions, miniDimensions, teleportDimensions);
}

void LanderSprite::setTexture(std::shared_ptr<StopWatch>& watch, bool& isTeleporting)
{
	auto _time = watch->time_elapsed();

	if (isTeleporting)
	{
		auto period = 0.12f;
		if (_time >= 0.0f && _time <= period)
		{
			updateAnimationSpriteTexture(landerTeleport1_t, miniMap_t);
			return;
		}

		if (_time > period && _time <= 2 * period)
		{
			updateAnimationSpriteTexture(landerTeleport2_t, miniMap_t);
			return;
		}

		if (_time > 2 * period && _time <= 3 * period)
		{
			updateAnimationSpriteTexture(landerTeleport3_t, miniMap_t);
			return;
		}

		if (_time > 3 * period && _time <= 4 * period)
		{
			updateAnimationSpriteTexture(landerTeleport4_t, miniMap_t);
			return;
		}

		isTeleporting = false;
		watch->restart();
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
		return;
	}

	if (_time > 4 * sprite_period && _time <= 5 * sprite_period)
	{
		updateSpriteTexture(lander5_t, miniMap_t);
		return;
	}

	if (_time > 5 * sprite_period && _time <= 6 * sprite_period)
	{
		updateSpriteTexture(lander6_t, miniMap_t);
		return;
	}

	if (_time > 6 * sprite_period && _time <= 7 * sprite_period)
	{
		updateSpriteTexture(lander7_t, miniMap_t);
		return;
	}

	if (_time > 7 * sprite_period && _time <= 8 * sprite_period)
	{
		updateSpriteTexture(lander8_t, miniMap_t);
		return;
	}

	if (_time > 8 * sprite_period && _time <= 9 * sprite_period)
	{
		updateSpriteTexture(lander9_t, miniMap_t);
		return;
	}

	if (_time > 9 * sprite_period && _time <= 10 * sprite_period)
	{
		updateSpriteTexture(lander10_t, miniMap_t);
		return;
	}

	if (_time > 10 * sprite_period && _time <= 11 * sprite_period)
	{
		updateSpriteTexture(lander11_t, miniMap_t);
		return;
	}

	if (_time > 11 * sprite_period && _time <= 12 * sprite_period)
	{
		updateSpriteTexture(lander12_t, miniMap_t);
		return;
	}

	if (_time > 12 * sprite_period && _time <= 13 * sprite_period)
	{
		updateSpriteTexture(lander13_t, miniMap_t);
		return;
	}

	if (_time > 13 * sprite_period && _time <= 14 * sprite_period)
	{
		updateSpriteTexture(lander14_t, miniMap_t);
		return;
	}

	if (_time > 14 * sprite_period && _time <= 15 * sprite_period)
	{
		updateSpriteTexture(lander15_t, miniMap_t);
		return;
	}

	if (_time > 15 * sprite_period && _time <= 16 * sprite_period)
	{
		updateSpriteTexture(lander16_t, miniMap_t);
		return;
	}

	watch->restart();
}

void LanderSprite::loadTextures()
{
	landerTeleport1_t.loadFromFile("resources/lander-teleport1.png");
	landerTeleport2_t.loadFromFile("resources/lander-teleport2.png");
	landerTeleport3_t.loadFromFile("resources/lander-teleport3.png");
	landerTeleport4_t.loadFromFile("resources/lander-teleport4.png");

	lander1_t.loadFromFile("resources/lander1.png");
	lander2_t.loadFromFile("resources/lander2.png");
	lander3_t.loadFromFile("resources/lander3.png");
	lander4_t.loadFromFile("resources/lander4.png");
	lander5_t.loadFromFile("resources/lander5.png");
	lander6_t.loadFromFile("resources/lander6.png");
	lander7_t.loadFromFile("resources/lander7.png");
	lander8_t.loadFromFile("resources/lander8.png");
	lander9_t.loadFromFile("resources/lander9.png");
	lander10_t.loadFromFile("resources/lander10.png");
	lander11_t.loadFromFile("resources/lander11.png");
	lander12_t.loadFromFile("resources/lander13.png");
	lander13_t.loadFromFile("resources/lander13.png");
	lander14_t.loadFromFile("resources/lander14.png");
	lander15_t.loadFromFile("resources/lander15.png");
	lander16_t.loadFromFile("resources/lander16.png");
	miniMap_t.loadFromFile("resources/mini-lander.png");
}
#include "landerSprite.h"

LanderSprite::LanderSprite():
	sprite_period{0.3f} //display each sprite for 0.5 sec
{
	sf::Vector2f mainDimensions;
	mainDimensions.x = 16.0f;
	mainDimensions.y = 16.0f;

	sf::Vector2f miniDimensions;
	miniDimensions.x = 13.0f;
	miniDimensions.y = 5.0f;

	sf::Vector2f teleportDimensions;
	teleportDimensions.x = 100.0f;
	teleportDimensions.y = 100.0f;

	loadTextures();
	InitialiseEntityOrigin(mainDimensions, miniDimensions, teleportDimensions);
}

void LanderSprite::setTexture(std::shared_ptr<StopWatch>& watch, bool& isTeleporting)
{
	auto _time = watch->time_elapsed();

	if (isTeleporting)
	{
		auto period = 7.0f / 90.0f;
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

		if (_time > 4 * period && _time <= 5 * period)
		{
			updateAnimationSpriteTexture(landerTeleport5_t, miniMap_t);
			return;
		}

		if (_time > 5 * period && _time <= 6 * period)
		{
			updateAnimationSpriteTexture(landerTeleport6_t, miniMap_t);
			return;
		}

		if (_time > 6 * period && _time <= 7 * period)
		{
			updateAnimationSpriteTexture(landerTeleport7_t, miniMap_t);
			return;
		}

		if (_time > 7 * period && _time <= 8 * period)
		{
			updateAnimationSpriteTexture(landerTeleport8_t, miniMap_t);
			return;
		}

		if (_time > 8 * period && _time <= 9 * period)
		{
			updateAnimationSpriteTexture(landerTeleport9_t, miniMap_t);
			isTeleporting = false;
			watch->restart();
			return;
		}
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
	landerTeleport2_t.loadFromFile("resources/lander-teleport-2.png");
	landerTeleport3_t.loadFromFile("resources/lander-teleport-3.png");
	landerTeleport4_t.loadFromFile("resources/lander-teleport-4.png");
	landerTeleport5_t.loadFromFile("resources/lander-teleport-5.png");
	landerTeleport6_t.loadFromFile("resources/lander-teleport-6.png");
	landerTeleport7_t.loadFromFile("resources/lander-teleport-7.png");
	landerTeleport8_t.loadFromFile("resources/lander-teleport-8.png");
	landerTeleport9_t.loadFromFile("resources/lander-teleport-9.png");
	lander1_t.loadFromFile("resources/lander1.png");
	lander2_t.loadFromFile("resources/lander2.png");
	lander3_t.loadFromFile("resources/lander3.png");
	lander4_t.loadFromFile("resources/lander4.png");
	miniMap_t.loadFromFile("resources/mini-lander.png");
}
#include "missileSprite.h"

MissileSprite::MissileSprite():
	sprite_period{0.2f}
{
	sf::Vector2f dimensions;
	dimensions.x = 6.0f;
	dimensions.y = 6.0f;
	loadTextures();
	InitialiseEntityOrigin(dimensions);
}

void MissileSprite::loadTextures()
{
	missile1_t.loadFromFile("resources/missile1.png");
	missile2_t.loadFromFile("resources/missile2.png");
}

void MissileSprite::setTexture(std::shared_ptr<StopWatch>& watch)
{
	auto _time = watch->time_elapsed();

	if (_time == 0 && _time <= sprite_period)
	{
		updateSpriteTexture(missile1_t);
		return;
	}

	if (_time > sprite_period && _time <= 2 * sprite_period)
	{
		updateSpriteTexture(missile2_t);
		watch->restart();
	}
}

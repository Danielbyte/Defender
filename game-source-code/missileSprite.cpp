#include "missileSprite.h"

MissileSprite::MissileSprite():
	sprite_period{0.2f}
{
	sf::Vector2f dimensions;
	dimensions.x = 6.0f;
	dimensions.y = 6.0f;
	sf::Vector2f miniDimensions;
	sf::Vector2f NA;
	loadTextures();
	InitialiseEntityOrigin(dimensions, miniDimensions, NA);
}

void MissileSprite::loadTextures()
{
	missile1_t.loadFromFile("resources/missile1.png");
	missile2_t.loadFromFile("resources/missile2.png");
}

void MissileSprite::setTexture(const float _time)
{

	if (_time <= sprite_period)
	{
		updateSpriteTexture(missile1_t, NA);
		return;
	}

	if (_time > sprite_period)
	{
		updateSpriteTexture(missile2_t, NA);
	}
}

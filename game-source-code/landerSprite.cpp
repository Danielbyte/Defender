#include "landerSprite.h"

LanderSprite::LanderSprite()
{
	sf::Vector2f dimensions;
	dimensions.x = 32.0f;
	dimensions.y = 32.0f;
	loadTextures();
	InitialiseEntityOrigin(dimensions);
}

void LanderSprite::setTexture()
{

}

void LanderSprite::loadTextures()
{
	lander1_t.loadFromFile("resources/lander1.png");
	lander2_t.loadFromFile("resources/lander2.png");
	lander3_t.loadFromFile("resources/lander3.png");
	lander4_t.loadFromFile("resources/lander4.png");
}
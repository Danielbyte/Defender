#include "landscapeSprite.h"

LandscapeSprite::LandscapeSprite()
{
	sf::Vector2f dimensions;
	dimensions.x = 1200.0f;
	dimensions.y = 68.0f;
	loadTextures();
	InitialiseEntityOrigin(dimensions);
	updateSpriteTexture(pixel_t);
}

void LandscapeSprite::loadTextures()
{
	pixel_t.loadFromFile("resources/terrain-1.png");
}

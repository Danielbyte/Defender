#include "landscapeSprite.h"

LandscapeSprite::LandscapeSprite()
{
	sf::Vector2f dimensions;
	dimensions.x = 2.0f;
	dimensions.y = 2.0f;
	loadTextures();
	InitialiseEntityOrigin(dimensions);
	updateSpriteTexture(pixel_t);
}

void LandscapeSprite::loadTextures()
{
	pixel_t.loadFromFile("resources/terrain-pixel.png");
}

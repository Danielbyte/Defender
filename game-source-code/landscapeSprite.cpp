#include "landscapeSprite.h"

LandscapeSprite::LandscapeSprite(const int id)
{
	sf::Vector2f dimensions;
	dimensions.x = 3200.0f;
	dimensions.y = 100.0f;
	loadTextures();
	InitialiseEntityOrigin(dimensions);

	if (id == 1)
	updateSpriteTexture(terrain1_t);

	if (id == 2)
		updateSpriteTexture(terrain2_t);
}

void LandscapeSprite::loadTextures()
{
	terrain1_t.loadFromFile("resources/terrain-1.png");
	terrain2_t.loadFromFile("resources/terrain-2.png");
}

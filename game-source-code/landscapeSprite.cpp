#include "landscapeSprite.h"

LandscapeSprite::LandscapeSprite(const int id)
{
	sf::Vector2f dimensions;
	dimensions.x = 3200.0f;
	dimensions.y = 100.0f;
	sf::Vector2f miniDimensions;
	loadTextures();
	InitialiseEntityOrigin(dimensions, miniDimensions);

	if (id == 1)
	updateSpriteTexture(terrain1_t, miniMap_t);

	if (id == 2)
		updateSpriteTexture(terrain2_t, miniMap_t);
}

void LandscapeSprite::loadTextures()
{
	terrain1_t.loadFromFile("resources/terrain-1.png");
	terrain2_t.loadFromFile("resources/terrain-2.png");
}

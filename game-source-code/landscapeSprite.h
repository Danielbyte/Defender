#ifndef LANDSCAPESPRITE_H
#define LANDSCAPESPRITE_H

#include "spriteStore.h"

class LandscapeSprite : public SpriteStore
{
public:
	LandscapeSprite(const int id);
	void virtual loadTextures();

private:
	sf::Texture terrain1_t;
	sf::Texture terrain2_t;
	sf::Texture miniMap_t;
};
#endif // !LANDSCAPESPRITE_H


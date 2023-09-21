#ifndef LANDSCAPESPRITE_H
#define LANDSCAPESPRITE_H

#include "spriteStore.h"

class LandscapeSprite : public SpriteStore
{
public:
	LandscapeSprite();
	void virtual loadTextures();

private:
	sf::Texture pixel_t;
};
#endif // !LANDSCAPESPRITE_H


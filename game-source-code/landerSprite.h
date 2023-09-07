#ifndef LANDERSPRITE_H
#define LANDERSPRITE_H

#include "spriteStore.h"

class LanderSprite : public SpriteStore
{
public:
	LanderSprite();
	void virtual loadTextures();
	void setTexture();

private:
	sf::Texture lander1_t;
	sf::Texture lander2_t;
	sf::Texture lander3_t;
	sf::Texture lander4_t;

};
#endif // !LANDERSPRITE_H


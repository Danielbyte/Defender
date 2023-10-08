#ifndef BOMBERSPRITE_H
#define BOMBERSPRITE_H

#include "spriteStore.h"

class BomberSprite : public SpriteStore
{
public:
	BomberSprite();
	void virtual loadTextures();

private:
	sf::Texture bomber1_t;
	sf::Texture bomber2_t;
	sf::Texture bomber3_t;
	sf::Texture bomber4_t;
	sf::Texture bomber5_t;
	sf::Texture bomber6_t;
	sf::Texture bomber7_t;
};
#endif // !BOMBERSPRITE_H


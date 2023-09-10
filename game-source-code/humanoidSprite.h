#ifndef HUMANOIDSPRITE_H
#define HUMANOIDSPRITE_H

#include "spriteStore.h"

class HumanoidSprite : public SpriteStore
{
public:
	HumanoidSprite();
	void virtual loadTextures();
	void setTexture();

private:
	sf::Texture humanoidLeft1_t;
	sf::Texture humanoidLeft2_t;
	sf::Texture humanoidRight1_t;
	sf::Texture humanoidRight2_t;
	sf::Texture fallingHumanoid1_t;
	sf::Texture fallingHumanoid2_t;
	sf::Texture fallingHumanoid3_t;

};
#endif // !HUMANOIDSPRITE_H


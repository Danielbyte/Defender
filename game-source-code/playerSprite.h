#ifndef PLAYERSPRITE_H
#define PLAYERSPRITE_H

#include "spriteStore.h"

class PlayerSprite : public SpriteStore
{
public:
	PlayerSprite();
	void virtual loadTextures();
	void setTexture();

private:
	sf::Texture player_tR;
	sf::Texture player_tL;
};

#endif // !PLAYERSPRITE_H


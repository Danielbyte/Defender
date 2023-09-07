#ifndef PLAYERLASERSPRITE_H
#define PLAYERLASERSPRITE_H

#include "spriteStore.h"

class PlayerLaserSprite : public SpriteStore
{
public:
	PlayerLaserSprite();
	void virtual loadTextures();
	void setTexture();

private:
	sf::Texture redRight_t;
	sf::Texture redLeft_t;
	sf::Texture greenRight_t;
	sf::Texture greenLeft_t;
	sf::Texture blueRight_t;
	sf::Texture blueLeft_t;

};
#endif // !PLAYERLASERSPRITE_H





#ifndef PLAYERLASERSPRITE_H
#define PLAYERLASERSPRITE_H

#include "spriteStore.h"

class PlayerLaserSprite : public SpriteStore
{
public:
	PlayerLaserSprite();
	PlayerLaserSprite(const std::string& direction, const std::string& color);
	void virtual loadTextures();
	void setTexture(const std::string& direction, const std::string& color);
	sf::Texture getTexture();

private:
	sf::Texture redRight_t;
	sf::Texture redLeft_t;
	sf::Texture greenRight_t;
	sf::Texture greenLeft_t;
	sf::Texture blueRight_t;
	sf::Texture blueLeft_t;

};
#endif // !PLAYERLASERSPRITE_H





#ifndef LASERSPRITE_H
#define LASERSPRITE_H

#include "spriteStore.h"

class LaserSprite : public SpriteStore
{
public:
	LaserSprite();
	LaserSprite(const std::string& direction, const std::string& color);
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
	sf::Texture NA;

};
#endif // !PLAYERLASERSPRITE_H





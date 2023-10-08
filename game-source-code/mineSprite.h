#ifndef MINESPRITE_H
#define MINESPRITE_H

#include "spriteStore.h"

class MineSprite : public SpriteStore
{
public:
	MineSprite();
	void virtual loadTextures();
	void setTexture();

private:
	sf::Texture mine1_t;
	sf::Texture mine2_t;
	sf::Texture mini_t;
	std::shared_ptr<StopWatch>animation_watch = std::make_shared<StopWatch>();

};
#endif // !MINESPRITE_H


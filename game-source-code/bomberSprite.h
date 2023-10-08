#ifndef BOMBERSPRITE_H
#define BOMBERSPRITE_H

#include "spriteStore.h"

class BomberSprite : public SpriteStore
{
public:
	BomberSprite();
	void virtual loadTextures();
	void setTexture();

private:
	sf::Texture bomber1_t;
	sf::Texture bomber2_t;
	sf::Texture bomber3_t;
	sf::Texture bomber4_t;
	sf::Texture bomber5_t;
	sf::Texture bomber6_t;
	sf::Texture bomber7_t;
	std::shared_ptr<StopWatch> animation_watch = std::make_shared<StopWatch>();
	float period;
};
#endif // !BOMBERSPRITE_H


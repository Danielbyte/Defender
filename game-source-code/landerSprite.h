#ifndef LANDERSPRITE_H
#define LANDERSPRITE_H

#include "spriteStore.h"
#include "stopWatch.h"

class LanderSprite : public SpriteStore
{
public:
	LanderSprite();
	void virtual loadTextures();
	void setTexture(std::shared_ptr<StopWatch>& watch);

private:
	sf::Texture lander1_t;
	sf::Texture lander2_t;
	sf::Texture lander3_t;
	sf::Texture lander4_t;
	float sprite_period; //time witch a sprite should display

};
#endif // !LANDERSPRITE_H


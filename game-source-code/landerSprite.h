#ifndef LANDERSPRITE_H
#define LANDERSPRITE_H

#include "spriteStore.h"
#include "stopWatch.h"

class LanderSprite : public SpriteStore
{
public:
	LanderSprite();
	void virtual loadTextures();
	void setTexture(std::shared_ptr<StopWatch>& watch, const bool isTeleporting);

private:
	sf::Texture landerTeleport1_t;
	sf::Texture landerTeleport2_t;
	sf::Texture landerTeleport3_t;
	sf::Texture landerTeleport4_t;
	sf::Texture landerTeleport5_t;
	sf::Texture laderTeleport6_t;
	sf::Texture landerTeleport7_t;
	sf::Texture lander1_t;
	sf::Texture lander2_t;
	sf::Texture lander3_t;
	sf::Texture lander4_t;
	sf::Texture miniMap_t;
	float sprite_period; //time witch a sprite should display

};
#endif // !LANDERSPRITE_H


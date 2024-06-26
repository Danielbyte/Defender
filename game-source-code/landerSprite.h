#ifndef LANDERSPRITE_H
#define LANDERSPRITE_H

#include "spriteStore.h"
#include "stopWatch.h"

class LanderSprite : public SpriteStore
{
public:
	LanderSprite();
	void virtual loadTextures();
	void setTexture(std::shared_ptr<StopWatch>& watch, bool& isTeleporting, bool isShot, bool& isExploding, bool& canDelete,
		bool isAbducting);

private:
	sf::Texture landerTeleport1_t;
	sf::Texture landerTeleport2_t;
	sf::Texture landerTeleport3_t;
	sf::Texture landerTeleport4_t;
	sf::Texture landerTeleport5_t;
	sf::Texture landerTeleport6_t;
	sf::Texture landerTeleport7_t;
	sf::Texture landerTeleport8_t;
	sf::Texture landerTeleport9_t;

	//Lander textures
	sf::Texture lander1_t, lander2_t, lander3_t, lander4_t, lander5_t, lander6_t, lander7_t, lander8_t;
	sf::Texture lander9_t, lander10_t, lander11_t, lander12_t, lander13_t, lander14_t, lander15_t, lander16_t;

	//Explodinf lander textures
	sf::Texture explosion1_t, explosion2_t, explosion3_t, explosion4_t, explosion5_t, explosion6_t, explosion7_t;
	sf::Texture explosion8_t, explosion9_t, explosion10_t, explosion11_t, explosion12_t, explosion13_t, explosion14_t;

	sf::Texture miniMap_t;
	float sprite_period; //time witch a sprite should display
	bool startedExplosion;

};
#endif // !LANDERSPRITE_H


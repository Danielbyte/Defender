#ifndef HUMANOIDSPRITE_H
#define HUMANOIDSPRITE_H

#include "spriteStore.h"
#include "stopWatch.h"
#include "humanoid.h"

class HumanoidSprite : public SpriteStore
{
public:
	HumanoidSprite();
	void virtual loadTextures();
	void setTexture(std::string _direction, std::shared_ptr<StopWatch>& watch,const HumanoidState state);

private:
	sf::Texture humanoidLeft1_t;
	sf::Texture humanoidLeft2_t;
	sf::Texture humanoidRight1_t;
	sf::Texture humanoidRight2_t;
	sf::Texture fallingHumanoid1_t;
	sf::Texture fallingHumanoid2_t;
	sf::Texture fallingHumanoid3_t;

	float texture_period;
};
#endif // !HUMANOIDSPRITE_H


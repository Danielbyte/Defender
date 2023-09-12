#ifndef HUMANOIDSPRITE_H
#define HUMANOIDSPRITE_H

#include "spriteStore.h"
#include "stopWatch.h"
#include <iostream>

class HumanoidSprite : public SpriteStore
{
public:
	HumanoidSprite();
	void virtual loadTextures();
	void setTexture(std::string _direction, const std::string _state, float xPos, float yPos,
		std::shared_ptr<StopWatch>humanoid_watch);

private:
	void walkingAndAbuction(std::string direction, std::shared_ptr<StopWatch>humanoid_watch);
	void falling(std::string direction);

	sf::Texture humanoidLeft1_t;
	sf::Texture humanoidLeft2_t;
	sf::Texture humanoidRight1_t;
	sf::Texture humanoidRight2_t;
	sf::Texture fallingHumanoid1_t;
	sf::Texture fallingHumanoid2_t;
	sf::Texture fallingHumanoid3_t;

	float texture_period;

	//std::shared_ptr<StopWatch>humanoid_watch = std::make_shared<StopWatch>();
};
#endif // !HUMANOIDSPRITE_H


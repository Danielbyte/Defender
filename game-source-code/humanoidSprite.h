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
	void falling(std::string direction, std::shared_ptr<StopWatch>humanoid_watch);
	void turning(std::string direction, std::shared_ptr<StopWatch>humanoid_watch);

	//Textures of humanoid(s) moving to the left. (A more effecient way is to have a class that does sprite cutting)
	sf::Texture humanoid1_t, humanoid2_t, humanoid3_t, humanoid4_t, humanoid5_t, humanoid6_t, humanoid7_t, humanoid8_t, humanoid9_t, humanoid10_t;
	sf::Texture humanoid11_t, humanoid12_t, humanoid13_t, humanoid14_t, humanoid15_t, humanoid16_t, humanoid17_t, humanoid18_t, humanoid19_t, humanoid20_t;
	sf::Texture humanoid21_t, humanoid22_t, humanoid23_t, humanoid24_t, humanoid25_t, humanoid26_t, humanoid27_t, humanoid28_t, humanoid29_t, humanoid30_t;
	sf::Texture humanoid31_t, humanoid32_t, humanoid33_t, humanoid34_t;

	//Texture for turning humanoid (from left -> right)
	sf::Texture Thumanoid1_t, Thumanoid2_t, Thumanoid3_t, Thumanoid4_t, Thumanoid5_t, Thumanoid6_t, Thumanoid7_t, Thumanoid8_t, Thumanoid9_t, Thumanoid10_t;
	sf::Texture Thumanoid11_t, Thumanoid12_t, Thumanoid13_t, Thumanoid14_t, Thumanoid15_t, Thumanoid16_t, Thumanoid17_t, Thumanoid18_t, Thumanoid19_t, Thumanoid20_t;
	sf::Texture Thumanoid21_t, Thumanoid22_t, Thumanoid23_t, Thumanoid24_t, Thumanoid25_t, Thumanoid26_t, Thumanoid27_t, Thumanoid28_t;

	sf::Texture fallingHumanoid1_t;
	sf::Texture fallingHumanoid2_t;
	sf::Texture fallingHumanoid3_t;
	sf::Texture miniMap_t;

	float texture_period;

	//std::shared_ptr<StopWatch>humanoid_watch = std::make_shared<StopWatch>();
};
#endif // !HUMANOIDSPRITE_H


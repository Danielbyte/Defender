#include "humanoidSprite.h"

HumanoidSprite::HumanoidSprite():
	texture_period{1.0f}
{
	sf::Vector2f dimensions;
	dimensions.x = 8.0f;
	dimensions.y = 12.0f;
	InitialiseEntityOrigin(dimensions);
	loadTextures();
}

void HumanoidSprite::loadTextures()
{
	humanoidLeft1_t.loadFromFile("resources/humanoidleft-1.png");
	humanoidLeft2_t.loadFromFile("resources/humanoidleft-2.png");
	humanoidRight1_t.loadFromFile("resources/humanoidright-1.png");
	humanoidRight2_t.loadFromFile("resources/humanoidright-2.png");
	fallingHumanoid1_t.loadFromFile("resources/falling-humanoid1.png");
	fallingHumanoid2_t.loadFromFile("resources/falling-humanoid2.png");
	fallingHumanoid3_t.loadFromFile("resources/falling-humanoid3.png");
}

void HumanoidSprite::setTexture(std::string direction, std::shared_ptr<StopWatch>& watch, const HumanoidState state)
{

}
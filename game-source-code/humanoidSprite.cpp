#include "humanoidSprite.h"

HumanoidSprite::HumanoidSprite(){}

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

void HumanoidSprite::setTexture()
{

}
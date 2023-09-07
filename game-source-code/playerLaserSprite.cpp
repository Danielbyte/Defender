#include "playerLaserSprite.h"

PlayerLaserSprite::PlayerLaserSprite()
{
	loadTextures();
}

void PlayerLaserSprite::loadTextures()
{
	redRight_t.loadFromFile("resources/right-red-laser.png");
	redLeft_t.loadFromFile("resources/left-red-laser.png");
	greenRight_t.loadFromFile("resources/right-green-laser.png");
	greenLeft_t.loadFromFile("resources/left-green-laser.png");
	blueRight_t.loadFromFile("resources/right-blue-laser.png");
	blueLeft_t.loadFromFile("resources/left-blue-lase.png");
}
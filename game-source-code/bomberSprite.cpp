#include "bomberSprite.h"

BomberSprite::BomberSprite(){}

void BomberSprite::loadTextures()
{
	bomber1_t.loadFromFile("resources/bomber1.png");
	bomber2_t.loadFromFile("resources/bomber2.png");
	bomber3_t.loadFromFile("resources/bomber3.png");
	bomber4_t.loadFromFile("resources/bomber4.png");
	bomber5_t.loadFromFile("resources/bomber5.png");
	bomber6_t.loadFromFile("resources/bomber6.png");
	bomber7_t.loadFromFile("resources/bomber7.png");
}
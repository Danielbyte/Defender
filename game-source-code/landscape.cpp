#include "landscape.h"

Landscape::Landscape():
	yPosition{525.0f},
	xPosition{0}
{}

void Landscape::updateTerrain(std::shared_ptr<LandscapeSprite>& landscape_sprite,const float x_position)
{
	xPosition = x_position;
	auto NA = 0.0f;
	landscape_sprite->updateSpritePosition("either", xPosition, yPosition,NA, NA);
}

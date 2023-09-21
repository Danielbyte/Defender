#include "landscape.h"

Landscape::Landscape():
	yPosition{560.0f},
	xPosition{0}
{}

void Landscape::updateTerrain(std::shared_ptr<LandscapeSprite>& landscape_sprite,const float x_position)
{
	xPosition = x_position;
	landscape_sprite->updateSpritePosition("either", xPosition, yPosition);
}

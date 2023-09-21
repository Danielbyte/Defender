#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include <cmath>
#include <vector>
#include <memory>
#include "landscapeSprite.h"

class Landscape
{
public:
	Landscape();
	void updateTerrain(std::shared_ptr<LandscapeSprite>& landscape_sprites, const float x_position);

private:
	float yPosition;
	float xPosition;

};
#endif // !LANDSCAPE_H


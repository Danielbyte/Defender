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
	void createTerrain(std::vector<std::shared_ptr<LandscapeSprite>>& landscape_sprites, 
		std::vector<std::shared_ptr<Landscape>>& landscape, const int initPosition, const int finalPosiftion);
	void setPosition(const int x, const int y);
private:
	int yPosition;
	int xposition;

};
#endif // !LANDSCAPE_H


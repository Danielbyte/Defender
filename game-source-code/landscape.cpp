#include "landscape.h"

Landscape::Landscape():
	yPosition{0},
	xposition{0}
{}

void Landscape::createTerrain(std::vector<std::shared_ptr<LandscapeSprite>>& landscape_sprites,
	std::vector<std::shared_ptr<Landscape>>& landscape, const int initPosition, const int finalPosiftion)
{
	landscape.clear();
	landscape_sprites.clear();
	auto F = 127;

	for (int x_position = initPosition; x_position <= finalPosiftion; ++x_position)
	{
		auto landscape_point = std::make_shared<Landscape>();
		auto y_position = F + static_cast<int>(std::cos(static_cast<double>(x_position) / 5.0f) * -11.0);
		landscape_point->setPosition(x_position, y_position);
		landscape.push_back(landscape_point);

		auto landscape_pixel = std::make_shared<LandscapeSprite>();
		landscape_pixel->updateSpritePosition("either", static_cast<float>(x_position), static_cast<float>(y_position));
		landscape_sprites.push_back(landscape_pixel);
	}
	
}

void Landscape::setPosition(const int x, const int y)
{
	xposition = x;
	yPosition = y;
}

#include "mine.h"

Mine::Mine():
	xPosition{-100.0f},
	yPosition{-100.0f}
{}

Mine::Mine(float _xPosition, float _yPosition):
	xPosition{_xPosition},
	yPosition{_yPosition}
{
	lifeTime->restart();
}

std::tuple<float, float> Mine::getPosition() const
{
	return { xPosition, yPosition };
}

void Mine::updateMine(std::vector<std::shared_ptr<Mine>>& mines, std::vector<std::shared_ptr<MineSprite>>& mine_sprites)
{

}
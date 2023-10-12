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

float Mine::getLifeTime() const
{
	return lifeTime->time_elapsed();
}

void Mine::updateMine(std::vector<std::shared_ptr<Mine>>& mines, std::vector<std::shared_ptr<MineSprite>>& mine_sprites)
{
	auto mine = mines.begin();
	auto mine_sprite = mine_sprites.begin();
	auto NA = 0.0f;
	while (mine != mines.end())
	{
		auto [xPos, yPos] = (*mine)->getPosition();
		(*mine_sprite)->updateSpritePosition("either", xPos, yPos, NA, NA);
		(*mine_sprite)->setTexture();

		//Mine should detonate after 10 seconds
		if ((*mine)->getLifeTime() >= 10.0f)
		{
			mines.erase(mine);
			mine_sprites.erase(mine_sprite);
		}
		else
		{
			++mine;
			++mine_sprite;
		}
	}
}

void Mine::test_updateMine(std::vector<std::shared_ptr<Mine>>& mines, std::vector<std::shared_ptr<MineSprite>>& mine_sprites,
	float time)
{
	auto mine = mines.begin();
	auto mine_sprite = mine_sprites.begin();
	auto NA = 0.0f;
	while (mine != mines.end())
	{
		auto [xPos, yPos] = (*mine)->getPosition();
		(*mine_sprite)->updateSpritePosition("either", xPos, yPos, NA, NA);
		(*mine_sprite)->setTexture();

		//Mine should detonate after 10 seconds
		if (((*mine)->getLifeTime()+time) >= 10.0f)
		{
			mines.erase(mine);
			mine_sprites.erase(mine_sprite);
		}
		else
		{
			++mine;
			++mine_sprite;
		}
	}
}
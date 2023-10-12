#ifndef MINE_H
#define MINE_H

#include "mineSprite.h"

class Mine
{
public:
	Mine();
	Mine(float _xPosition, float _yPosition);
	std::tuple<float, float> getPosition() const;
	void updateMine(std::vector<std::shared_ptr<Mine>>& mines, std::vector<std::shared_ptr<MineSprite>>& mine_sprites);
	void test_updateMine(std::vector<std::shared_ptr<Mine>>& mines, std::vector<std::shared_ptr<MineSprite>>& mine_sprites,
		float time);
	float getLifeTime() const;

private:
	float xPosition;
	float yPosition;
	std::shared_ptr<StopWatch>lifeTime = std::make_shared<StopWatch>();
};
#endif // !MINE_H


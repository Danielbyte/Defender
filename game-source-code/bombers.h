#ifndef BOMBERS_H
#define BOMBERS_H

#include "player.h"
#include "bomberSprite.h"
#include "mineSprite.h"
#include "mine.h"

class Bombers
{
public:
	Bombers();
	Bombers(std::shared_ptr<Player>& player);
	void update(std::shared_ptr<Player>& player, std::shared_ptr<BomberSprite>& bomber_sprite,
		std::vector<std::shared_ptr<Mine>>& mines, std::vector<std::shared_ptr<MineSprite>>& mine_sprites,
		const float dt);
	void moveNorthEast(const float dt);
	void moveSouthEast(const float dt);
	void moveSouthWest(const float dt);
	void moveNorthWest(const float dt);
	void moveEast(const float dt);
	void moveWest(const float dt);
	std::tuple<float, float> getPosition() const;

private:
	float xPosition;
	float yPosition;
	bool moveLeft;
	bool moveRight;
	float bomberSpeed;

	void spawn(float playerXposition, float playerYposition, std::string playerDirection);
	void spawnMine(std::vector<std::shared_ptr<Mine>>& mines, std::vector<std::shared_ptr<MineSprite>>& mine_sprites);
};
#endif // !BOMBERS_H


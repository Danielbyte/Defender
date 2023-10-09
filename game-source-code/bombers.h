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
		std::vector<std::shared_ptr<Projectile>>& lasers, const float dt);

	void moveNorthEast(const float dt);
	void moveSouthEast(const float dt);
	void moveSouthWest(const float dt);
	void moveNorthWest(const float dt);
	void moveEast(const float dt);
	void moveWest(const float dt);
	bool avoidFire(const float playerYposition, const float dt);
	void moveNorth(const float dt);
	void moveSouth(const float dt);
	std::tuple<float, float> getPosition() const;
	std::tuple <float, float> getMiniMapPositrion();

private:
	float xPosition;
	float yPosition;
	bool moveLeft;
	bool moveRight;
	float bomberSpeed;
	bool isDodgingBullet;

	void spawn(float playerXposition, float playerYposition, std::string playerDirection);
	void spawnMine(std::vector<std::shared_ptr<Mine>>& mines, std::vector<std::shared_ptr<MineSprite>>& mine_sprites);

	std::shared_ptr<StopWatch>mine_plant = std::make_shared<StopWatch>();
	std::shared_ptr<StopWatch>dodge_missile = std::make_shared<StopWatch>();
};
#endif // !BOMBERS_H


#ifndef BOMBERS_H
#define BOMBERS_H
#include "player.h"

class Bombers
{
public:
	Bombers();
	Bombers(std::shared_ptr<Player>& player);
	void update(std::shared_ptr<Player>& player, const float dt);
	void moveNorthEast(const float dt);
	void moveSouthEast(const float dt);
	void moveSouthWest(const float dt);
	void moveNorthWest(const float dt);
	void moveEast(const float dt);
	void moveWest(const float dt);

private:
	float xPosition;
	float yPosition;
	bool moveLeft;
	bool moveRight;
	float bomberSpeed;

	void spawn(float playerXposition, float playerYposition, std::string playerDirection);
};
#endif // !BOMBERS_H


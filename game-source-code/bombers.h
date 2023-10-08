#ifndef BOMBERS_H
#define BOMBERS_H
#include "player.h"

class Bombers
{
public:
	Bombers();
	Bombers(std::shared_ptr<Player>& player);
	void update(std::shared_ptr<Player>& player);
	void moveNorthEast();
	void moveSouthEast();
	void moveSouthWest();
	void moveNorthWest();

private:
	float xPosition;
	float yPosition;
	bool moveLeft;
	bool moveRight;
	float bomberSpeed;

	void spawn(float playerXposition, float playerYposition, std::string playerDirection);
};
#endif // !BOMBERS_H


#ifndef BOMBERS_H
#define BOMBERS_H
#include "shooter.h"
#include "player.h"

class Bombers : public Shooter
{
public:
	Bombers();
	Bombers(std::shared_ptr<Player>& player);
	void update();

private:
	float xPosition;
	float yPosition;
	bool moveLeft;
	bool moveRight;

	void spawn(float playerXposition, float playerYposition, std::string playerDirection);
};
#endif // !BOMBERS_H


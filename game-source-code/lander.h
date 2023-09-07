#ifndef LANDER_H
#define LANDER_H

#include "shooter.h"
#include <random>

class Lander : public Shooter
{
public:
	Lander();
	std::tuple<float, float> getPosition() const;
	void generateInitialPosition();
	void updateLander(const float& dt);
	void moveEast();
	void moveWest();
	void moveNorth();
	void moveSouth();
	void moveNorthEast();
	void moveSouthEast();
	void moveSouthWest();
	void moveNorthWest();

private:
	float xPosition;
	float yPosition;
	bool rightSide;
	bool leftSide;
	float landerSpeed;
	bool reachedHumanoidZone;

};
#endif // !LANDER_H


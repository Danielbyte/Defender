#ifndef LANDER_H
#define LANDER_H

#include "shooter.h"
#include <random>

enum class Direction { North, South, East, West, NorthEast, SouthEast, SouthWest, NorthWest };

class Lander : public Shooter
{
public:
	Lander();
	std::tuple<float, float> getPosition() const;
	void generateInitialPosition();
	void updateLander(const float& dt);
	void moveEast(const float& dt);
	void moveWest(const float& dt);
	void moveNorth(const float& dt);
	void moveSouth(const float& dt);
	void moveNorthEast(const float& dt);
	void moveSouthEast(const float& dt);
	void moveSouthWest(const float& dt);
	void moveNorthWest(const float& dt);
	Direction pickDirection();

private:
	float xPosition;
	float yPosition;
	bool rightSide;
	bool leftSide;
	float landerSpeed;
	bool reachedHumanoidZone;
};
#endif // !LANDER_H


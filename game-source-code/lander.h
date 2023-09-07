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
	void updateLander();

private:
	float xPosition;
	float yPosition;

};
#endif // !LANDER_H


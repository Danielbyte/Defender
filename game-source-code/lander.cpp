#include "lander.h"

Lander::Lander():
	xPosition{0.0f},
	yPosition{0.0f}
{
	//generate spawn position
	generateInitialPosition();
}

std::tuple<float, float> Lander::getPosition() const
{
	return { xPosition,yPosition };
}

void Lander::generateInitialPosition()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	float minXposition = 16.0f;
	float maxXposition = 784.0f;
	std::uniform_real_distribution<float>distribution(minXposition, maxXposition);
	xPosition = distribution(gen);

	float minYposition = 16.0f;
	float maxYposition = 584.0f;
	std::uniform_real_distribution<float>distribution2(minYposition, maxYposition);
	yPosition = distribution2(gen);
}

void Lander::updateLander()
{

}
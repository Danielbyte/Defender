#include "lander.h"

Lander::Lander():
	xPosition{0.0f},
	yPosition{0.0f},
	leftSide{false},
	rightSide{false},
	landerSpeed{350.0f}
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
	auto middle = 400.0f;
	
	if (xPosition >= middle)
	{
		rightSide = true;
	}

	else
	{
		leftSide = true;
	}

	float minYposition = 16.0f;
	float maxYposition = 450.0f;
	std::uniform_real_distribution<float>distribution2(minYposition, maxYposition);
	yPosition = distribution2(gen);
}

void Lander::updateLander(const float& dt)
{
	if (yPosition < 450.0f)
	{
		yPosition += landerSpeed * dt;
		if (rightSide)
		{
			//lander needs to move left
			xPosition -= landerSpeed * dt;
		}

		if (leftSide)
		{
			//lander needs to move right
			xPosition += landerSpeed * dt;
		}
	}

	if (yPosition >= 450.0f)
	{
		//decide whether to move diagonally up/down or move in a straight horizontal line
		std::random_device rd;
		std::mt19937 gen(rd());
		float min = 0;
		float max = 2;
		std::uniform_int_distribution<int>distribution(min, max);
		auto decision = distribution(gen);
	}
}
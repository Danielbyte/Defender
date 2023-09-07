#include "lander.h"

Lander::Lander():
	xPosition{0.0f},
	yPosition{0.0f},
	leftSide{false},
	rightSide{false},
	landerSpeed{350.0f},
	reachedHumanoidZone{false}
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
	if (yPosition < 450.0f && !reachedHumanoidZone)
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
		reachedHumanoidZone = true;
		//decide whether to move diagonally up/down or move in a straight horizontal line
		std::random_device rd;
		std::mt19937 gen(rd());
		float min = 0;
		float max = 2;
		std::uniform_int_distribution<int>distribution(min, max);
		auto decision = distribution(gen);
		
		if (decision == 0)
		{
			//move Horizontally straight
		}

		if (decision == 1)
		{
			//move Horizontally down
		}

		if (decision == 2)
		{
			//move Horizontally up
		}
	}
}

void Lander::moveEast(const float& dt)
{
	xPosition += landerSpeed * dt;
}

void Lander::moveWest(const float& dt)
{
	xPosition -= landerSpeed * dt;
}

void Lander::moveNorth(const float& dt)
{
	yPosition -= landerSpeed * dt;
}

void Lander::moveSouth(const float& dt)
{
	yPosition += landerSpeed * dt;
}

void Lander::moveNorthEast(const float& dt)
{
	xPosition += landerSpeed * dt;
	yPosition -= landerSpeed * dt;
}

void Lander::moveSouthEast(const float& dt)
{
	xPosition += landerSpeed * dt;
	yPosition += landerSpeed * dt;
}

void Lander::moveSouthWest(const float& dt)
{
	xPosition -= landerSpeed * dt;
	yPosition += landerSpeed * dt;
}

void Lander::moveNorthWest(const float& dt)
{
	xPosition -= landerSpeed * dt;
	yPosition -= landerSpeed * dt;
}
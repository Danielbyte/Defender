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
	float maxYposition = 400.0f;
	std::uniform_real_distribution<float>distribution2(minYposition, maxYposition);
	yPosition = distribution2(gen);
}

void Lander::updateLander(const float& dt)
{
	if (!reachedHumanoidZone)
	{
		if (rightSide)
		{
			//lander needs to move south westerly
			moveSouthWest(dt);
		}

		if (leftSide)
		{
			//lander needs to move south easterly
			moveSouthEast(dt);
		}

		if (yPosition >= 450.0f)
			reachedHumanoidZone = true;
	}

	if (reachedHumanoidZone)
	{
		//Lander should Hover around humanoid zone
		Direction direction = pickDirection();
		switch (direction)
		{
		case Direction::North:
			moveNorth(dt);
			break;
		case Direction::South:
			moveSouth(dt);
			break;
		case Direction::East:
			moveEast(dt);
			break;
		case Direction::West:
			moveWest(dt);
			break;
		case Direction::NorthEast:
			moveNorthEast(dt);
			break;
		case Direction::SouthEast:
			moveSouthEast(dt);
			break;
		case Direction::SouthWest:
			moveSouthWest(dt);
			break;
		case Direction::NorthWest:
			moveNorthWest(dt);
			break;
		default:
			break;
		}
	}
}

void Lander::moveEast(const float& dt)
{
	xPosition += landerSpeed * dt;
	restrictLander();
}

void Lander::moveWest(const float& dt)
{
	xPosition -= landerSpeed * dt;
	restrictLander();
}

void Lander::moveNorth(const float& dt)
{
	yPosition -= landerSpeed * dt;
	restrictLander();
}

void Lander::moveSouth(const float& dt)
{
	yPosition += landerSpeed * dt;
	restrictLander();
}

void Lander::moveNorthEast(const float& dt)
{
	xPosition += landerSpeed * dt;
	yPosition -= landerSpeed * dt;
	restrictLander();
}

void Lander::moveSouthEast(const float& dt)
{
	xPosition += landerSpeed * dt;
	yPosition += landerSpeed * dt;
	restrictLander();
}

void Lander::moveSouthWest(const float& dt)
{
	xPosition -= landerSpeed * dt;
	yPosition += landerSpeed * dt;
	restrictLander();
}

void Lander::moveNorthWest(const float& dt)
{
	xPosition -= landerSpeed * dt;
	yPosition -= landerSpeed * dt;
	restrictLander();
}

Direction Lander::pickDirection()
{
	if (rightSide)
	{
		//decide whether to move diagonally up/down or move in a straight horizontal line
		std::random_device rd;
		std::mt19937 gen(rd());
		float min = 0;
		float max = 4;
		std::uniform_int_distribution<int>distribution(min, max);
		auto decision = distribution(gen);

		if (decision == 0)
		{
			//move south westerly
			return Direction::SouthWest;
		}

		if (decision == 1)
		{
			//move westerly
			return Direction::West;
		}

		if (decision == 2)
		{
			//move north westerly
			return Direction::NorthWest;
		}

		if (decision == 3)
		{
			//move northerly
			return Direction::North;
		}

		if (decision == 4)
		{
			//move south
			return Direction::South;
		}
	}

	else
	{
		//decide whether to move diagonally up/down or move in a straight horizontal line
		std::random_device rd;
		std::mt19937 gen(rd());
		float min = 3;
		float max = 7;
		std::uniform_int_distribution<int>distribution(min, max);
		auto decision = distribution(gen);

		if (decision == 3)
		{
			//move south North
			return Direction::North;
		}

		if (decision == 4)
		{
			//move south
			return Direction::South;
		}

		if (decision == 5)
		{
			//move south easterly
			return Direction::SouthEast;
		}

		if (decision == 6)
		{
			//move easterly
			return Direction::East;
		}

		if (decision == 7)
		{
			//move north easterly
			return Direction::NorthEast;
		}
	}
}

void Lander::restrictLander()
{
	if (!reachedHumanoidZone)
		return;

	if (yPosition >= 470.0f)
		yPosition = 470.0f;

	if (yPosition <= 430.0f)
		yPosition = 430.0f;
}
#include "lander.h"

Lander::Lander():
	xPosition{0.0f},
	yPosition{0.0f},
	leftSide{false},
	rightSide{false},
	landerSpeed{50.0f},
	reachedHumanoidZone{false},
	direction{Direction::Unknown},
	playerXposref{0.0f},
	playerYposref{0.0f}
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

void Lander::updateLander(std::shared_ptr<LanderSprite>& lander_sprite, const float& dt, 
	std::shared_ptr<Player>& player)
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

		if (yPosition >= 480.0f)
			reachedHumanoidZone = true;
	}

	if (reachedHumanoidZone)
	{
		//Lander should Hover around humanoid zone
		pickDirection();
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

	auto [x, y] = player->getPlayerPosition();
	playerXposref = x;
	playerYposref = y;

	lander_sprite->setTexture(lander_watch);
	lander_sprite->updateSpritePosition("either", xPosition, yPosition);
}

void Lander::moveEast(const float& dt)
{
	xPosition += landerSpeed * dt;
	restrictLander(dt);
}

void Lander::moveWest(const float& dt)
{
	xPosition -= landerSpeed * dt;
	restrictLander(dt);
}

void Lander::moveNorth(const float& dt)
{
	yPosition -= landerSpeed * dt;
	restrictLander(dt);
}

void Lander::moveSouth(const float& dt)
{
	yPosition += landerSpeed * dt;
	restrictLander(dt);
}

void Lander::moveNorthEast(const float& dt)
{
	xPosition += landerSpeed * dt;
	yPosition -= landerSpeed * dt;
	restrictLander(dt);
}

void Lander::moveSouthEast(const float& dt)
{
	xPosition += landerSpeed * dt;
	yPosition += landerSpeed * dt;
	restrictLander(dt);
}

void Lander::moveSouthWest(const float& dt)
{
	xPosition -= landerSpeed * dt;
	yPosition += landerSpeed * dt;
	restrictLander(dt);
}

void Lander::moveNorthWest(const float& dt)
{
	xPosition -= landerSpeed * dt;
	yPosition -= landerSpeed * dt;
	restrictLander(dt);
}

void Lander::pickDirection()
{
	if (movement_watch->time_elapsed() < 1.5f)
		return;

	if (rightSide)
	{
		//decide whether to move diagonally up/down or move in a straight horizontal line
		std::random_device rd;
		std::mt19937 gen(rd());
		int min = 0;
		int max = 4;
		std::uniform_int_distribution<int>distribution(min, max);
		auto decision = distribution(gen);

		if (decision == 0)
		{
			//move south westerly
			movement_watch->restart();
			direction = Direction::SouthWest;
			return;
		}

		if (decision == 1)
		{
			//move westerly
			movement_watch->restart();
			direction = Direction::West;
			return;
		}

		if (decision == 2)
		{
			//move north westerly
			movement_watch->restart();
			direction = Direction::NorthWest;
			return;
		}

		if (decision == 3)
		{
			//move northerly
			movement_watch->restart();
			direction = Direction::North;
			return;
		}

		if (decision == 4)
		{
			//move south
			movement_watch->restart();
			direction = Direction::South;
			return;
		}
	}

	else
	{
		//decide whether to move diagonally up/down or move in a straight horizontal line
		std::random_device rd;
		std::mt19937 gen(rd());
		int min = 3;
		int max = 7;
		std::uniform_int_distribution<int>distribution(min, max);
		auto decision = distribution(gen);

		if (decision == 3)
		{
			//move south North
			movement_watch->restart();
			direction = Direction::North;
			return;
		}

		if (decision == 4)
		{
			//move south
			movement_watch->restart();
			direction = Direction::South;
			return;
		}

		if (decision == 5)
		{
			//move south easterly
			movement_watch->restart();
			direction = Direction::SouthEast;
			return;
		}

		if (decision == 6)
		{
			//move easterly
			movement_watch->restart();
			direction = Direction::East;
			return;
		}

		if (decision == 7)
		{
			//move north easterly
			movement_watch->restart();
			direction = Direction::NorthEast;
			return;
		}
	}
}

void Lander::restrictLander(const float& dt)
{
	if (!reachedHumanoidZone)
		return;

	if (yPosition >= 505.0f)
	{
		if (leftSide)
			direction = Direction::NorthEast;

		if (rightSide)
			direction = Direction::NorthWest;

		return;
	}

	if (yPosition <= 455.0f)
	{
		if (leftSide)
			direction = Direction::SouthEast;

		if (rightSide)
			direction = Direction::SouthWest;
	}
}

void Lander::updateProjectile(const float& dt)
{
	if (projectiles.empty())
		return;

	auto missile_iter = projectiles.begin();

	while (missile_iter != projectiles.end())
	{
		auto _direction = (*missile_iter)->getProjectileDirection();

		if (_direction == "left")
		{
			auto newX = xPosition - 100.0f * dt;
			auto newY = ((newX - xPosition) / (playerXposref - xPosition)) * (playerYposref - yPosition) + yPosition;
			(*missile_iter)->updateProjectileCoordinates(newX, newY);
		}

		if (_direction == "right")
		{
			auto newX = xPosition + 100.0f * dt;
			auto newY = ((newX - xPosition) / (playerXposref - xPosition)) * (playerYposref - yPosition) + yPosition;
			(*missile_iter)->updateProjectileCoordinates(newX, newY);
		}
		++missile_iter;
	}
}

void Lander::createMissiles()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	int min = 0;
	int max = 70000;
	std::uniform_int_distribution<int>distribution(min, max);
	auto decision = distribution(gen);

	if (decision % 5 == 0)
	{
		//Lander is on the left of player
		if (xPosition < playerXposref)
		{
			//missile should move right
			auto missile = std::make_shared<Shooter>(xPosition,yPosition,"right",0.0f,0.0f);
			projectiles.push_back(missile);
		}

		//Lander is on the right of player
		if (xPosition > playerXposref)
		{
			//missile should move left
			auto missile = std::make_shared<Shooter>(xPosition, yPosition, "left", 0.0f, 0.0f);
			projectiles.push_back(missile);
		}
	}
}
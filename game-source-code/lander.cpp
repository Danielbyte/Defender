#include "lander.h"

Lander::Lander():
	xPosition{0.0f},
	yPosition{0.0f},
	leftSide{false},
	rightSide{false},
	landerSpeed{50.0f},
	reachedHumanoidZone{false},
	direction{Direction::Other},
	playerXposref{0.0f},
	playerYposref{0.0f},
	missileSpeed{150.0f},
	isAbducting{false},
	ascend{false},
	localId{0}
{}

Lander::Lander(std::shared_ptr<Player>& player):
	xPosition{ 0.0f },
	yPosition{ 0.0f },
	leftSide{ false },
	rightSide{ false },
	landerSpeed{ 50.0f },
	reachedHumanoidZone{ false },
	direction{ Direction::Other },
	playerXposref{ 0.0f },
	playerYposref{ 0.0f },
	missileSpeed{ 150.0f },
	isAbducting{ false },
	ascend{ false },
	localId{ 0 }
{
	//generate spawn position
	generateInitialPosition(player);
	setId();
	setLocalId();
}

std::tuple<float, float> Lander::getPosition() const
{
	return { xPosition,yPosition };
}

void Lander::generateInitialPosition(std::shared_ptr<Player>& player)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	float minXposition = -10.0f;
	float maxXposition = 100.0f;
	std::uniform_real_distribution<float>distribution(minXposition, maxXposition);
	xPosition = distribution(gen);
	auto [playerXpos, playerYpos] = player->getPlayerPosition();
	auto middle = playerXpos;
	
	if (xPosition >= middle)
	{
		rightSide = true;
	}

	else
	{
		leftSide = true;
	}

	float minYposition = 116.0f;
	float maxYposition = 400.0f;
	std::uniform_real_distribution<float>distribution2(minYposition, maxYposition);
	yPosition = distribution2(gen);
}

void Lander::updateLander(std::shared_ptr<LanderSprite>& lander_sprite, const float dt, 
	std::shared_ptr<Player>& player, std::vector<std::shared_ptr<MissileSprite>>& missile_sprites,
	std::vector<std::shared_ptr<Humanoid>>& humanoids)
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
		pickDirection(humanoids,dt);
		if (!isAbducting)
		{
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

	auto [x, y] = player->getPlayerPosition();
	playerXposref = x;
	playerYposref = y;
	createMissiles(missile_sprites);
	updateProjectile(dt, ProjectileType::LanderMissile);
	updateMissileSprites(missile_sprites);

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

void Lander::pickDirection(std::vector<std::shared_ptr<Humanoid>>& humanoids, const float dt)
{
	//Check if there is a humanoid beneath
	auto humanoidBeneath = checkForHumanoid(humanoids);
	if (humanoidBeneath)
	   abductionDecision();//decide whether to ubduct it or not

	if (isAbducting)
		abductionProcess(dt); //Lander has decided to abduct
	
	if (isAbducting)
		return;

	//if decided to abduct, do abduction operations
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
	if (!reachedHumanoidZone || isAbducting)
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

void Lander::createMissiles(std::vector<std::shared_ptr<MissileSprite>>& missile_sprites)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	int min = 0;
	int max = 700;
	std::uniform_int_distribution<int>distribution(min, max);
	auto decision = distribution(gen);

	if (decision < 3)
	{
		//Lander is on the left of player
		if (xPosition < playerXposref)
		{
			//missile should move right
			auto horizontalOffset = 0.0f;
			auto verticalOffset = 0.0f;
			auto Id = projectiles.size() + 1;
			auto missile = std::make_shared<Projectile>(xPosition,yPosition,"right",horizontalOffset,verticalOffset,
				playerXposref,playerYposref,Id,ProjectileType::LanderMissile,missileSpeed);

			createProjectile(missile);

			auto missile_sprite = std::make_shared<MissileSprite>();
			missile_sprites.push_back(missile_sprite);
			return;
		}

		//Lander is on the right of player
		if (xPosition > playerXposref)
		{
			//missile should move left
			auto horizontalOffset = 0.0f;
			auto verticalOffset = 0.0f;
			auto Id = projectiles.size() + 1;
			auto missile = std::make_shared<Projectile>(xPosition, yPosition, "left", horizontalOffset,
				verticalOffset,playerXposref,playerYposref, Id,ProjectileType::LanderMissile,missileSpeed);

			createProjectile(missile);

			auto missile_sprite = std::make_shared<MissileSprite>();
			missile_sprites.push_back(missile_sprite);
		}
	}
}

void Lander::updateMissileSprites(std::vector<std::shared_ptr<MissileSprite>>& missile_sprites)
{
	if (projectiles.empty())
		return;

	auto missile_obj = projectiles.begin();
	auto missile_sprite = missile_sprites.begin();

	while (missile_obj != projectiles.end())
	{
		if ((*missile_obj)->getType() == ProjectileType::LanderMissile)
		{
			auto [x, y] = (*missile_obj)->getProjectilePosition();
			(*missile_sprite)->updateSpritePosition("either", x, y);
			(*missile_obj)->updateFrameCounter();
			auto frame = (*missile_obj)->getFrameCounter();
			(*missile_sprite)->setTexture(frame);
			++missile_obj;
			++missile_sprite;
		}

		else
		{
			++missile_obj;
		}
	}
}

bool Lander::checkForHumanoid(std::vector<std::shared_ptr<Humanoid>>& humanoids)
{
	if (isAbducting)
		return false;

	for (auto& humanoid : humanoids)
	{
		auto humanoid_state  = humanoid->getHumanoidState();
		
		auto [humanoidXpos, humanoidYpos] = humanoid->getPosition();
		auto distance_betwwen = std::fabs(xPosition - humanoidXpos);
		if (distance_betwwen <= 0.4f && humanoid_state == HumanoidState::Walking)
		{
			return true;
		}
			
	}
	return false;
}

void Lander::abductionDecision()
{
	if (isAbducting)
		return;

	std::random_device rd;
	std::mt19937 gen(rd());
	int min = 1;
	int max = 2578;
	std::uniform_int_distribution<int>distribution(min, max);
	auto decision = distribution(gen);
	auto threshold = 1000;

	if (decision <= threshold && reachedHumanoidZone)
	{
		isAbducting = true;
		return;
	}
}

void Lander::setToascend()
{
	ascend = true;
}

void Lander::abductionProcess(const float dt)
{
	direction = Direction::Other;
	if (!ascend)
	{
		moveSouth(dt);
		return;
	}

	moveNorth(dt);
}

void Lander::setId()
{
	++globalId;
}

void Lander::setLocalId()
{
	localId = globalId;
}

unsigned int Lander::getLocalId()
{
	return localId;
}

unsigned int Lander::globalId = 0;

std::tuple<bool, bool> Lander::test_getSide()
{
	return { rightSide, leftSide };
}
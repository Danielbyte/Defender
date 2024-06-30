#include "lander.h"

Lander::Lander():
	xPosition{0.0f},
	yPosition{0.0f},
	leftSide{false},
	rightSide{false},
	landerSpeed{120.0f},
	reachedHumanoidZone{false},
	direction{Direction::Other},
	playerXposref{0.0f},
	playerYposref{0.0f},
	missileSpeed{150.0f},
	isAbducting{false},
	ascend{false},
	isTeleporting{true},
	isShot{false},
	isExploding{false},
	canDelete{false},
	localId{0}
{}

Lander::Lander(std::shared_ptr<Player>& player, bool isInitial):
	leftSide{ false },
	rightSide{ false },
	landerSpeed{ 120.0f },
	reachedHumanoidZone{ false },
	direction{ Direction::Other },
	playerXposref{ 0.0f },
	playerYposref{ 0.0f },
	missileSpeed{ 150.0f },
	isAbducting{ false },
	ascend{ false },
	isTeleporting{true},
	isShot{false},
	isExploding{false},
	canDelete{false},
	localId{ 0 }
{
	//increment number of landers evertime an instance of a lander is created
	++NumberOfLanders;

	//generate spawn position
	generateInitialPosition(player, isInitial);
	setId();
	setLocalId();
	lander_watch->restart();
}

std::tuple<float, float> Lander::getPosition() const
{
	return { xPosition,yPosition };
}

void Lander::generateInitialPosition(std::shared_ptr<Player>& player, bool isInitial)
{
	generateTeleportPosition(player, isInitial);

	auto [playerXpos, playerYpos] = player->getPlayerPosition();
	if (xPosition >= playerXpos) // lander on right side of player
	{
		rightSide = true;
	}

	else
	{
		leftSide = true; // lander on left side of player
	}
}

void Lander::updateLander(std::shared_ptr<LanderSprite>& lander_sprite, const float dt, 
	std::shared_ptr<Player>& player, std::vector<std::shared_ptr<MissileSprite>>& missile_sprites,
	std::vector<std::shared_ptr<Humanoid>>& humanoids)
{
	if (isShot)
	{
		auto horizontalOffset = 400.0f;
		auto verticalOffset = 40.0f;
		auto horizontallScalingFactor = 0.5f;
		auto verticalScalingFactor = (1.0f / 6.0f);

		auto miniMapXpos = (xPosition - horizontalOffset) * horizontallScalingFactor;
		auto miniMapYpos = (yPosition - verticalOffset) * verticalScalingFactor;

		lander_sprite->setTexture(lander_watch, isTeleporting, isShot, isExploding, canDelete,isAbducting);
		lander_sprite->updateSpritePosition("either", xPosition, yPosition, miniMapXpos, miniMapYpos);
		return;
	}
		
	if (!reachedHumanoidZone && !isTeleporting)
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
		landerSpeed = 80.0f; //lander at humanoid zone
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

	if (!isTeleporting)
		createMissiles(missile_sprites);

	auto horizontalOffset = 400.0f;
	auto verticalOffset = 40.0f;
	auto horizontallScalingFactor = 0.5f;
	auto verticalScalingFactor = (1.0f / 6.0f);

	auto miniMapXpos = (xPosition - horizontalOffset) * horizontallScalingFactor;
	auto miniMapYpos = (yPosition - verticalOffset) * verticalScalingFactor;
	lander_sprite->setTexture(lander_watch, isTeleporting, isShot, isShot, canDelete, isAbducting);
	lander_sprite->updateSpritePosition("either", xPosition, yPosition, miniMapXpos, miniMapYpos);
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
	restrictLander(dt);
}

bool Lander::canRemove() const
{
	return canDelete;
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
		//move westerly
		movement_watch->restart();
		direction = Direction::West;
		return;
	}

	//move easterly
	movement_watch->restart();
	direction = Direction::East;	
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
			auto missile = std::make_shared<Projectile>(xPosition,yPosition,"right",horizontalOffset,verticalOffset,
				playerXposref,playerYposref, ProjectileType::LanderMissile,missileSpeed);

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
			auto missile = std::make_shared<Projectile>(xPosition, yPosition, "left", horizontalOffset,
				verticalOffset,playerXposref,playerYposref,ProjectileType::LanderMissile,missileSpeed);

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

	auto horizontalOffset = 400.0f;
	auto verticalOffset = 0.0f;
	auto miniMapXpos = xPosition - horizontalOffset;
	auto miniMapYpos = yPosition - verticalOffset;
	auto missile_obj = projectiles.begin();
	auto missile_sprite = missile_sprites.begin();

	while (missile_obj != projectiles.end())
	{

		auto [x, y] = (*missile_obj)->getProjectilePosition();
		(*missile_sprite)->updateSpritePosition("either", x, y, miniMapXpos,miniMapYpos);
		(*missile_obj)->updateFrameCounter();
		auto frame = (*missile_obj)->getFrameCounter();
		(*missile_sprite)->setTexture(frame);
		++missile_obj;
		++missile_sprite;
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
		auto distance_between = std::fabs(xPosition - humanoidXpos);
		if (distance_between <= 0.4f && humanoid_state == HumanoidState::Walking)
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

bool Lander::test_getIfInHumanoidZone() const
{
	return reachedHumanoidZone;
}

void Lander::generateTeleportPosition(std::shared_ptr<Player>& player, bool initial_lander)
{
	if (initial_lander)
	{
		//Initial y position is the same for all landers.
		yPosition = 150.0f;
		switch (NumberOfLanders)
		{
		case 1:
		case 2:
			xPosition = 1350.0f - (NumberOfLanders - 1) * 250.0f;
			break;

		case 3:
		case 4:
			xPosition = -1550.0f + (NumberOfLanders + 1) * 250.0f;
			break;

		default:
			break;
		}
		
		return;
	}
}

bool Lander::getIfTeleporting() const
{
	return isTeleporting;
}

void Lander::test_setTeleportationState(bool teleporting)
{
	isTeleporting = teleporting;
}

void Lander::setPosition(float x, float y)
{
	xPosition = x;
	yPosition = y;
}

void Lander::setSide(bool isRight, bool isLeft)
{
	rightSide = isRight;
	leftSide = isLeft;
}

bool Lander::getIsAbducting() const
{
	return isAbducting;
}

void Lander::setToExplode()
{
	isShot = true;
	isExploding = true;
	isAbducting = false;
}

std::tuple<bool, bool> Lander::getLanderStatus() const
{
	return { isShot, isExploding };
}

//Static variables are accessed at class level
int Lander::NumberOfLanders = 0; //initialise
#include "bombers.h"
Bombers::Bombers():
	xPosition{-5.0f},
	yPosition{-5.0f},
	moveLeft{false},
	moveRight{false},
	bomberSpeed{50.0f},
	isDodgingBullet{false}
{}

Bombers::Bombers(std::shared_ptr<Player>& player):
	xPosition{-5.0f},
	yPosition{-5.0f},
	moveLeft{false},
	moveRight{false},
	bomberSpeed{50.0f},
	isDodgingBullet{false}
{
	auto [xPlayerPos, yPlayerPos] = player->getPlayerPosition();
	auto playerDirection = player->getDirection();
	spawn(xPlayerPos, yPlayerPos, playerDirection);
	mine_plant->restart();
}

void Bombers::spawn(float playerXposition, float playerYposition, std::string playerDirection)
{
	if (playerDirection == "left")
	{
		xPosition = playerXposition - 500.0f;
		moveRight = true;
	}
		

	if (playerDirection == "right")
	{
		xPosition = playerXposition + 500.0f;
		moveLeft = true;
	}
		
	yPosition = playerYposition;
	if (playerYposition >= 480.0f || playerYposition <= 150.0f)
		yPosition = 400.0f;	

}

void Bombers::update(std::shared_ptr<Player>& player, std::shared_ptr<BomberSprite>& bomber_sprite,
	std::vector<std::shared_ptr<Mine>>& mines, std::vector<std::shared_ptr<MineSprite>>& mine_sprites, 
	std::vector<std::shared_ptr<Projectile>>& lasers, const float dt)
{
	auto [playerXpos, playerYpos] = player->getPlayerPosition();
	
	if (!isDodgingBullet)
	{
		isDodgingBullet = avoidFire(playerYpos, dt);

		if (isDodgingBullet)
		{
			dodge_missile->restart();
		}	
	}

	if (isDodgingBullet)
	{
		if (dodge_missile->time_elapsed() >= 5.0f)
		{
			isDodgingBullet = false;
			dodge_missile->restart();
		}
	}
		

	if (moveLeft)
	{
		if (playerYpos > yPosition)
		{
			moveSouthWest(dt);
			bomber_sprite->setTexture();
			auto [miniXpos, miniYpos] = getMiniMapPositrion();
			bomber_sprite->updateSpritePosition("either", xPosition, yPosition, miniXpos, miniYpos);
			spawnMine(mines, mine_sprites);
			return;
		}

		if (playerYpos < yPosition)
		{
			moveNorthWest(dt);
			bomber_sprite->setTexture();
			auto [miniXpos, miniYpos] = getMiniMapPositrion();
			bomber_sprite->updateSpritePosition("either", xPosition, yPosition, miniXpos, miniYpos);
			spawnMine(mines, mine_sprites);
			return;
		}

		moveWest(dt);
		bomber_sprite->setTexture();
		auto [miniXpos, miniYpos] = getMiniMapPositrion();
		bomber_sprite->updateSpritePosition("either", xPosition, yPosition, miniXpos, miniYpos);
		spawnMine(mines, mine_sprites);
	}

	if (moveRight)
	{
		if (playerYpos < yPosition)
		{
			moveNorthEast(dt);
			bomber_sprite->setTexture();
			auto [miniXpos, miniYpos] = getMiniMapPositrion();
			bomber_sprite->updateSpritePosition("either", xPosition, yPosition, miniXpos, miniYpos);
			spawnMine(mines, mine_sprites);
			return;
		}

		if (playerYpos > yPosition)
		{
			moveSouthEast(dt);
			bomber_sprite->setTexture();
			auto [miniXpos, miniYpos] = getMiniMapPositrion();
			bomber_sprite->updateSpritePosition("either", xPosition, yPosition, miniXpos, miniYpos);
			spawnMine(mines, mine_sprites);
			return;
		}

		moveEast(dt);
		bomber_sprite->setTexture();
		auto [miniXpos, miniYpos] = getMiniMapPositrion();
		bomber_sprite->updateSpritePosition("either", xPosition, yPosition, miniXpos, miniYpos);
	}

	spawnMine(mines, mine_sprites);
}

void Bombers::moveNorthEast(const float dt)
{
	xPosition += bomberSpeed * dt;
	yPosition -= bomberSpeed * dt;

	if (yPosition <= 150.0f)
		moveEast(dt);
}

void Bombers::moveSouthEast(const float dt)
{
	xPosition += bomberSpeed * dt;
	yPosition += bomberSpeed * dt;

	if (yPosition >= 480.0f)
		moveEast(dt);
}

void Bombers::moveSouthWest(const float dt)
{
	xPosition -= bomberSpeed * dt;
	yPosition += bomberSpeed * dt;

	if (yPosition >= 480.0f)
		moveNorthWest(dt);
}

void Bombers::moveNorthWest(const float dt)
{
	xPosition -= bomberSpeed * dt;
	yPosition -= bomberSpeed * dt;

	if (yPosition <= 150.0f)
		moveWest(dt);
}

void Bombers::moveEast(const float dt)
{
	xPosition += bomberSpeed * dt;
}

void Bombers::moveWest(const float dt)
{
	xPosition -= bomberSpeed * dt;
}

std::tuple<float, float> Bombers::getPosition() const
{
	return { xPosition, yPosition };
}

void Bombers::spawnMine(std::vector<std::shared_ptr<Mine>>& mines,
	std::vector<std::shared_ptr<MineSprite>>& mine_sprites)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	int min = 0;
	int max = 11;
	std::uniform_int_distribution<int>distribution(min, max);

	auto decision = distribution(gen);
	auto time = mine_plant->time_elapsed();

	if (decision <= 5 && time >= 2.0f)
	{
		auto mine = std::make_shared<Mine>(xPosition, yPosition);
		mines.push_back(mine);
		auto mine_sprite = std::make_shared<MineSprite>();
		mine_sprites.push_back(mine_sprite);
		mine_plant->restart();
	}

	auto mine_obj = std::make_shared<Mine>();
	mine_obj->updateMine(mines, mine_sprites);
}

bool Bombers::avoidFire(const float playerYposition, const float dt)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	int min = 0;
	int max = 11;
	std::uniform_int_distribution<int>distribution(min, max);

	auto decision = distribution(gen);
	auto sameLevel = false;

	if (decision > 5)
	{
		return true;
	}
	
	return false;
}

void Bombers::moveNorth(const float dt)
{
	if (yPosition <= 150.0f)
	{
		moveSouth(dt);
		return;
	}
		
	yPosition -= bomberSpeed * dt;
}

void Bombers::moveSouth(const float dt)
{
	if (yPosition >= 480)
	{
		moveNorth(dt);
		return;
	}

	yPosition += bomberSpeed * dt;
}

std::tuple <float, float> Bombers::getMiniMapPositrion()
{
	auto horizontalOffset = 400.0f;
	auto verticalOffset = 40.0f;
	auto horizontallScalingFactor = 0.5f;
	auto verticalScalingFactor = (1.0f / 6.0f);

	auto miniMapXpos = (xPosition - horizontalOffset) * horizontallScalingFactor;
	auto miniMapYpos = (yPosition - verticalOffset) * verticalScalingFactor;

	return { miniMapXpos, miniMapYpos };
}

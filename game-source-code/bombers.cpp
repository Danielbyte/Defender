#include "bombers.h"
Bombers::Bombers():
	xPosition{-5.0f},
	yPosition{-5.0f},
	moveLeft{false},
	moveRight{false},
	bomberSpeed{50.0f}
{}

Bombers::Bombers(std::shared_ptr<Player>& player):
	xPosition{-5.0f},
	yPosition{-5.0f},
	moveLeft{false},
	moveRight{false},
	bomberSpeed{50.0f}
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
	const float dt)
{
	auto [playerXpos, playerYpos] = player->getPlayerPosition();
	
	if (moveLeft)
	{
		if (playerYpos > yPosition)
		{
			moveSouthWest(dt);
			bomber_sprite->setTexture();
			bomber_sprite->updateSpritePosition("either", xPosition, yPosition, 0.0f, 0.0f);
			spawnMine(mines, mine_sprites);
			return;
		}

		if (playerYpos < yPosition)
		{
			moveNorthWest(dt);
			bomber_sprite->setTexture();
			bomber_sprite->updateSpritePosition("either", xPosition, yPosition, 0.0f, 0.0f);
			spawnMine(mines, mine_sprites);
			return;
		}

		moveWest(dt);
		bomber_sprite->setTexture();
		bomber_sprite->updateSpritePosition("either", xPosition, yPosition, 0.0f, 0.0f);
		spawnMine(mines, mine_sprites);
	}

	if (moveRight)
	{
		if (playerYpos < yPosition)
		{
			moveNorthEast(dt);
			bomber_sprite->setTexture();
			bomber_sprite->updateSpritePosition("either", xPosition, yPosition, 0.0f, 0.0f);
			spawnMine(mines, mine_sprites);
			return;
		}

		if (playerYpos > yPosition)
		{
			moveSouthEast(dt);
			bomber_sprite->setTexture();
			bomber_sprite->updateSpritePosition("either", xPosition, yPosition, 0.0f, 0.0f);
			spawnMine(mines, mine_sprites);
			return;
		}

		moveEast(dt);
		bomber_sprite->setTexture();
		bomber_sprite->updateSpritePosition("either", xPosition, yPosition, 0.0f, 0.0f);
		spawnMine(mines, mine_sprites);
	}
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

	if (decision <= 5 && time >= 3.0f)
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


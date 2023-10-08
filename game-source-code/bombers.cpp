#include "bombers.h"
Bombers::Bombers():
	xPosition{-5.0f},
	yPosition{-5.0f},
	moveLeft{false},
	moveRight{false},
	bomberSpeed{300.0f}
{}

Bombers::Bombers(std::shared_ptr<Player>& player):
	xPosition{-5.0f},
	yPosition{-5.0f},
	moveLeft{false},
	moveRight{false},
	bomberSpeed{300.0f}
{
	auto [xPlayerPos, yPlayerPos] = player->getPlayerPosition();
	auto playerDirection = player->getDirection();
	spawn(xPlayerPos, yPlayerPos, playerDirection);
}

void Bombers::spawn(float playerXposition, float playerYposition, std::string playerDirection)
{
	if (playerDirection == "left")
	{
		xPosition = playerXposition - 200.0f;
		moveRight = true;
	}
		

	if (playerDirection == "right")
	{
		xPosition = playerXposition + 200.0f;
		moveLeft = true;
	}
		
	yPosition = playerYposition;
	if (playerYposition >= 480.0f || playerYposition <= 150.0f)
		yPosition = 400.0f;	
}

void Bombers::update(std::shared_ptr<Player>& player, const float dt)
{
	auto [playerXpos, playerYpos] = player->getPlayerPosition();

	if (moveLeft)
	{
		if (playerYpos > yPosition)
		{
			moveSouthWest(dt);
			return;
		}

		if (playerYpos < yPosition)
		{
			moveNorthWest(dt);
			return;
		}
	}

	if (moveRight)
	{
		if (playerYpos < yPosition)
		{
			moveNorthEast(dt);
			return;
		}

		if (playerYpos > yPosition)
		{
			moveSouthEast(dt);
			return;
		}
	}
}

void Bombers::moveNorthEast(const float dt)
{

}

void Bombers::moveSouthEast(const float dt)
{

}

void Bombers::moveSouthWest(const float dt)
{

}

void Bombers::moveNorthWest(const float dt)
{

}


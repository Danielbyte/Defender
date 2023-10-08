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
		moveLeft;
	}
		
	yPosition = playerYposition;
	if (playerYposition >= 480.0f || playerYposition <= 150.0f)
		yPosition = 400.0f;	
}

void Bombers::update(std::shared_ptr<Player>& player)
{
	auto [playerXpos, playerYpos] = player->getPlayerPosition();

	if (yPosition > playerYpos)
	{

	}

	if (yPosition < playerXpos)
	{

	}
}

void Bombers::moveNorthEast()
{

}

void Bombers::moveSouthEast()
{

}

void Bombers::moveSouthWest()
{

}

void Bombers::moveNorthWest()
{

}


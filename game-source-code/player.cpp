#include "player.h"

Player::Player():
	movementConstant{250.0f}
{
	x_playerPosition = 25.0f;
	y_playerPosition = 300.0f;
}

void Player::updatePlayer(const bool& left, const bool& right, const bool up, const bool& down,
	std::shared_ptr<SpriteStore>& sprite_store,const float& dt)
{
	if (right)
	{
		sprite_store->updatePlayerShipSprite("right",x_playerPosition,y_playerPosition);
		float rightBoundary = 800.0f - 25.0f;
		x_playerPosition += movementConstant * dt;
		//restrict player ship to right boundary
		if (x_playerPosition >= rightBoundary)
			x_playerPosition = rightBoundary;
	}

	if (left)
	{
		sprite_store->updatePlayerShipSprite("left",x_playerPosition,y_playerPosition);
		float leftBoundary = 25.0f;
		x_playerPosition -= movementConstant * dt;
		//Restrict player ship to left boundary
		if (x_playerPosition <= leftBoundary)
			x_playerPosition = leftBoundary;
	}

	if (up)
	{
		std::cout << "Player moving up" << std::endl;
	}

	if (down)
	{
		std::cout << "Player moving down" << std::endl;
	}

	sprite_store->updatePlayerShipSprite("either", x_playerPosition, y_playerPosition);
}

std::tuple<float,float> Player::getPlayerPosition() const
{
	return { x_playerPosition,y_playerPosition };
}

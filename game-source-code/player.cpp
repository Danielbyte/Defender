#include "player.h"

Player::Player()
{
	x_playerPosition = 25.0f;
	y_playerPosition = 300.0f;
}

void Player::updatePlayer(const bool& left, const bool& right, const bool up, const bool& down,
	std::shared_ptr<SpriteStore>& sprite_store)
{
	if (right)
	{
		sprite_store->updatePlayerShipSprite("right",x_playerPosition,y_playerPosition);
	}

	if (left)
	{
		sprite_store->updatePlayerShipSprite("left",x_playerPosition,y_playerPosition);
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

#include "player.h"

Player::Player(){}

void Player::updatePlayer(const bool& left, const bool& right, const bool up, const bool& down)
{
	if (right)
	{
		std::cout << "Player moving right" << std::endl;
	}

	if (left)
	{
		std::cout << "Player moving left" << std::endl;
	}

	if (up)
	{
		std::cout << "Player moving up" << std::endl;
	}

	if (down)
	{
		std::cout << "Player moving down" << std::endl;
	}
}
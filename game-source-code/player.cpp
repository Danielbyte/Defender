#include "player.h"

Player::Player():
	movementConstant{250.0f}
{
	x_playerPosition = 25.0f;
	y_playerPosition = 300.0f;
}

void Player::updatePlayer(const bool& left, const bool& right, const bool& up, const bool& down,bool& space,
	                      std::shared_ptr<PlayerSprite>& player_sprite,
	                      std::vector<std::shared_ptr<Projectile>>& laser_projectile, 
	                      std::vector<std::shared_ptr<PlayerLaserSprite>>& laser_sprite,const float& dt)
{
	if (space)
	{
		auto laser_pr = std::make_shared<Projectile>(Projectile(x_playerPosition, y_playerPosition, "right"));
		laser_projectile.push_back(laser_pr);
		//generate color of laser
		std::random_device rd;
		std::mt19937 gen(rd());
		int min = 0;
		int max = 2;
		std::uniform_int_distribution<int>distribution(min, max);
		auto laser_color = distribution(gen);
		if (laser_color == 0)
		{
			//generate green laser
			auto laser_sp = std::make_shared<PlayerLaserSprite>(PlayerLaserSprite());
		}

		if (laser_color == 1)
		{
			//generate red laser
			auto laser_sp = std::make_shared<PlayerLaserSprite>(PlayerLaserSprite());
		}

		if (laser_color == 2)
		{
			//generate blue laser
			auto laser_sp = std::make_shared<PlayerLaserSprite>(PlayerLaserSprite());
		}
		

		space = false;
	}

	if (right)
	{
		player_sprite->updateSpritePosition("right",x_playerPosition,y_playerPosition);
		float rightBoundary = 800.0f - 25.0f;
		x_playerPosition += movementConstant * dt;
		//restrict player ship to right boundary
		if (x_playerPosition >= rightBoundary)
			x_playerPosition = rightBoundary;
	}

	if (left)
	{
		player_sprite->updateSpritePosition("left",x_playerPosition,y_playerPosition);
		float leftBoundary = 25.0f;
		x_playerPosition -= movementConstant * dt;
		//Restrict player ship to left boundary
		if (x_playerPosition <= leftBoundary)
			x_playerPosition = leftBoundary;
	}

	if (up)
	{
		y_playerPosition -= movementConstant * dt;
		float upBoundary = 10.0f;
		//Restrict player ship to updwards boundary of game window
		if (y_playerPosition <= upBoundary)
			y_playerPosition = upBoundary;

	}

	if (down)
	{
		y_playerPosition += movementConstant * dt;
		float downBoundary = 600.0f - 10.0f;
		//Restrict player ship to downwards boundary of game window
		if (y_playerPosition >= downBoundary)
			y_playerPosition = downBoundary;
	}

	player_sprite->updateSpritePosition("either", x_playerPosition, y_playerPosition);
	player_sprite->setTexture();
}

std::tuple<float,float> Player::getPlayerPosition() const
{
	return { x_playerPosition,y_playerPosition };
}

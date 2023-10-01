#include "player.h"

Player::Player():
	playerSpeed{250.0f},
	laserSpeed{700.0f},
	state{PlayerState::Alive}
{
	x_playerPosition = 400.0f;
	y_playerPosition = 300.0f; 
	direction = "right"; //player initially facing right
}

void Player::updatePlayer(const bool& left, const bool& right, const bool& up, const bool& down,bool& space,
	std::shared_ptr<PlayerSprite>& player_sprite, std::vector<std::shared_ptr<LaserSprite>>& laser_sprite, const float dt,
	bool& gameOver)
{
	auto horizontalOffset = 400.0f;
	auto verticalOffset = 40.0f;
	auto horizontallScalingFactor = 0.5f;
	auto verticalScalingFactor = (1.0f / 6.0f);
	auto miniMapXpos = (x_playerPosition - horizontalOffset) * horizontallScalingFactor;
	auto miniMapYpos = (y_playerPosition - verticalOffset) * verticalScalingFactor;

	if (space)
	{
		createLasers(laser_sprite);
		space = false;
	}

	if (right)
	{
		direction = "right";
		player_sprite->updateSpritePosition(direction,x_playerPosition,y_playerPosition,miniMapXpos,miniMapYpos);
		float rightBoundary = 800.0f - 25.0f;
		x_playerPosition += playerSpeed * dt;
	}

	if (left)
	{
		direction = "left";
		player_sprite->updateSpritePosition(direction,x_playerPosition,y_playerPosition,miniMapXpos, miniMapYpos);
		float leftBoundary = 25.0f;
		x_playerPosition -= playerSpeed * dt;
	}

	if (up)
	{
		y_playerPosition -= playerSpeed * dt;
		float upBoundary = 110.0f;
		//Restrict player ship to updwards boundary of game window
		if (y_playerPosition <= upBoundary)
			y_playerPosition = upBoundary;
	}

	if (down)
	{
		y_playerPosition += playerSpeed * dt;
		float downBoundary = 600.0f - 10.0f;
		//Restrict player ship to downwards boundary of game window
		if (y_playerPosition >= downBoundary)
			y_playerPosition = downBoundary;
	}
	
	player_sprite->updateSpritePosition("either", x_playerPosition, y_playerPosition,miniMapXpos, miniMapYpos);

	switch (state)
	{
	case PlayerState::Alive:
		player_sprite->setTexture("alive", gameOver ,animation_watch);
		break;
	case PlayerState::Dead:
	    player_sprite->setTexture("dead", gameOver, animation_watch);
		return;
		break;
	default:
		break;
	}
	
	updateLasers(laser_sprite, dt);
}

void Player::createLasers(std::vector<std::shared_ptr<LaserSprite>>& laser_sprite)
{
	auto horizontalOffset = 74.0f;
	auto verticalOffset = 5.0f;
	auto id = projectiles.size() + 1;
	auto laser_pr = std::make_shared<Projectile>(Projectile(x_playerPosition, y_playerPosition, direction,
		horizontalOffset, verticalOffset,x_playerPosition,y_playerPosition,id,ProjectileType::Laser,laserSpeed));

	createProjectile(laser_pr);
	//projectiles.push_back(laser_pr);

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
		auto laser_sp = std::make_shared<LaserSprite>(LaserSprite(direction, "green"));
		laser_sp->setTexture(direction, "green");
		laser_sprite.push_back(laser_sp);
	}

	if (laser_color == 1)
	{
		//generate red laser
		auto laser_sp = std::make_shared<LaserSprite>(LaserSprite(direction, "red"));
		laser_sp->setTexture(direction, "red");
		laser_sprite.push_back(laser_sp);
	}

	if (laser_color == 2)
	{
		//generate blue laser
		auto laser_sp = std::make_shared<LaserSprite>(LaserSprite(direction, "blue"));
		laser_sp->setTexture(direction, "blue");
		laser_sprite.push_back(laser_sp);
	}
}

void Player::updateLasers(std::vector<std::shared_ptr<LaserSprite>>& laser_sprite, const float dt)
{
	if (projectiles.empty())
		return;

	auto projectile_iter = projectiles.begin();
	auto laser_sprite_iter = laser_sprite.begin();
	auto laserSpeed = 600.0f;
	updateProjectile(dt, ProjectileType::Laser);
	auto NA = 0.0f; //none applicable fiels

	while (projectile_iter != projectiles.end())
	{
		if ((*projectile_iter)->getType() == ProjectileType::Laser)
		{
			auto [x, y] = (*projectile_iter)->getProjectilePosition();
			(*laser_sprite_iter)->updateSpritePosition("either", x, y, NA, NA);
			++projectile_iter;
			++laser_sprite_iter;
		}
		else
		{
			++projectile_iter;
		}
	}
}

std::tuple<float,float> Player::getPlayerPosition() const
{
	return { x_playerPosition,y_playerPosition };
}

std::string Player::getDirection() const
{
	return direction;
}

void Player::restartAnimationWatch()
{
	animation_watch.restart();
}

void Player::setPlayerState(PlayerState _state)
{
	state = _state;
}

PlayerState Player::getPlayerState() const
{
	return state;
}
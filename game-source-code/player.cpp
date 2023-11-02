#include "player.h"

Player::Player():
	playerSpeed{250.0f},
	laserSpeed{650.0f},
	state{PlayerState::Alive},
	playerScore{0}
{
	x_playerPosition = 400.0f;
	y_playerPosition = 300.0f; 
	direction = "right"; //player initially facing right
}

void Player::updatePlayer(const bool& left, const bool& right, const bool& up, const bool& down,bool& space,
	std::shared_ptr<PlayerSprite>& player_sprite, std::vector<std::shared_ptr<LaserSprite>>& laser_sprite, 
	std::vector<std::shared_ptr<Projectile>>& lasers,const float dt, bool& gameOver)
{
	auto horizontalOffset = 400.0f;
	auto verticalOffset = 40.0f;
	auto horizontallScalingFactor = 0.5f;
	auto verticalScalingFactor = (1.0f / 6.0f);
	auto miniMapXpos = (x_playerPosition - horizontalOffset) * horizontallScalingFactor;
	auto miniMapYpos = (y_playerPosition - verticalOffset) * verticalScalingFactor;

	if (space && state != PlayerState::Dead)
	{
		createLasers(laser_sprite, lasers);
		space = false;
	}

	if (right && state != PlayerState::Dead)
	{
		direction = "right";
		player_sprite->updateSpritePosition(direction,x_playerPosition,y_playerPosition,miniMapXpos,miniMapYpos);
		float rightBoundary = 800.0f - 25.0f;
		x_playerPosition += playerSpeed * dt;
	}

	if (left && state != PlayerState::Dead)
	{
		direction = "left";
		player_sprite->updateSpritePosition(direction,x_playerPosition,y_playerPosition,miniMapXpos, miniMapYpos);
		float leftBoundary = 25.0f;
		x_playerPosition -= playerSpeed * dt;
	}

	if (up && state != PlayerState::Dead)
	{
		y_playerPosition -= playerSpeed * dt;
		float upBoundary = 110.0f;
		//Restrict player ship to updwards boundary of game window
		if (y_playerPosition <= upBoundary)
			y_playerPosition = upBoundary;
	}

	if (down && state != PlayerState::Dead)
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
	
	if (state == PlayerState::Dead)
		return;

	updateLasers(laser_sprite, lasers, dt);
}

void Player::createLasers(std::vector<std::shared_ptr<LaserSprite>>& laser_sprite, std::vector<std::shared_ptr<Projectile>>& lasers)
{
	auto horizontalOffset = 74.0f;
	auto verticalOffset = 5.0f;
	auto laser_projectile = std::make_shared<Projectile>(Projectile(x_playerPosition, y_playerPosition, direction,
		horizontalOffset, verticalOffset,x_playerPosition,y_playerPosition, ProjectileType::Laser,laserSpeed));
	lasers.push_back(laser_projectile);


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

void Player::updateLasers(std::vector<std::shared_ptr<LaserSprite>>& laser_sprites, 
	std::vector<std::shared_ptr<Projectile>>& lasers, const float dt)
{
	if (lasers.empty())
		return;

	updateProjectile(dt, lasers, laser_sprites);
	auto laser = lasers.begin();
	auto laser_sprite = laser_sprites.begin();
	auto laserSpeed = 600.0f;
	auto NA = 0.0f; //none applicable fields

	while (laser != lasers.end())
	{
			auto [x, y] = (*laser)->getProjectilePosition();
			(*laser_sprite)->updateSpritePosition("either", x, y, NA, NA);
			++laser_sprite;
			++laser;
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

void Player::updatePlayerScore(const int points)
{
	playerScore += points;
}

int Player::getScore() const
{
	return playerScore;
}
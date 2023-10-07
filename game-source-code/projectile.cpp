#include "projectile.h"

Projectile::Projectile():
	initialXpos{0.0f},
	initialYpos{0.0f},
	xPosition{ 00.0f },
	yPosition{ -100.0f },
	targetXpos{ 0.0f },
	targetYpos{ 0.0f },
	frame_counter{0},
	slope{0.0f},
	yIntercept{0.0f},
	projectileId{0},
	speed{0.0f},
	Delete{false}
{}

Projectile::Projectile(const float x, const float y, const std::string _direction, const float horizontalOffset,
	const float verticalOffset,const float _targetXpos, const float _targetYpos, unsigned long long int _projectileId,
	ProjectileType _typeOfShooter, const float _speed)
{
	direction = _direction;
	yPosition = y + verticalOffset;
	initialYpos = yPosition;

	if (direction == "right")
	{
		xPosition = x + horizontalOffset;
		initialXpos = xPosition;
	}

	if (direction == "left")
	{
		xPosition = x - horizontalOffset;
		initialXpos = xPosition;
	}

	targetXpos = _targetXpos;
	if (_typeOfShooter == ProjectileType::Laser) { targetYpos = initialYpos; }
	else { targetYpos = _targetYpos; }
	
	if (_typeOfShooter == ProjectileType::LanderMissile)
		projectileId = _projectileId;

	typeOfShooter = _typeOfShooter;
	calculateTrajectoryConstants();
	speed = _speed;
	Delete = false;
	lifeTime->restart();
	color_watch->restart();
}

std::string Projectile::getProjectileDirection() const
{
	return direction;
}

std::tuple<float, float> Projectile::getProjectilePosition() const
{
	return { xPosition, yPosition };
}

void Projectile::updateFrameCounter()
{
	if (color_watch->time_elapsed() >= 0.4f)
	{
		color_watch->restart();
	}
}

float Projectile::getFrameCounter() const
{
	return color_watch->time_elapsed();
}

bool Projectile::getDelete() const
{
	return Delete;
}

void Projectile::calculateTrajectoryConstants()
{
	slope = (initialYpos - targetYpos) / (initialXpos - targetXpos);
	yIntercept = initialYpos - (slope * initialXpos);
}

void Projectile::updateTrajectory(const float x)
{
	xPosition = x;
	yPosition = (slope * x) + yIntercept;

	if (lifeTime->time_elapsed() >= 1.0f)
		Delete = true;

	if (yPosition <= 100.0f)
		Delete = true;
		//std::cout << "Delete" << std::endl;
}

void Projectile::updatePosition(const float x, const float y)
{
	xPosition = x;
	yPosition = y;
}

unsigned long long int Projectile::getProjectileId() const
{
	return projectileId;
}

ProjectileType Projectile::getType() const
{
	return typeOfShooter;
}

float Projectile::getSpeed() const
{
	return speed;
}

void Projectile::setNewId(unsigned long long int newId)
{
	projectileId = newId;
}
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
	typeOfShooter{ProjectileType::unknown},
	speed{0.0f},
	Delete{false}
{}

Projectile::Projectile(const float x, const float y, const std::string _direction, const float horizontalOffset,
	const float verticalOffset,const float _targetXpos, const float _targetYpos, ProjectileType _typeOfShooter, const float _speed)
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
	
	if (_typeOfShooter != ProjectileType::Laser)
	{
		setId();
		setProjectileId();
	}

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
	yPosition = (slope * xPosition) + yIntercept;

	if (lifeTime->time_elapsed() >= 1.0f)
		Delete = true;
}

void Projectile::updatePosition(const float x, const float y)
{
	xPosition = x;
	yPosition = y;
}

float Projectile::getLifeTime() const
{
	return lifeTime->time_elapsed();
}

unsigned long long int Projectile::getProjectileId() const
{
	return projectileId;
}

ProjectileType Projectile::getType() const
{
	return typeOfShooter;
}

float Projectile::getSpeed()
{
	if (slope >= 2.0f || slope <= -2.0f)
		speed = 10.0f;

	return speed;
}

void Projectile::setId()
{
	++projectileId_G;
}

void Projectile::setProjectileId()
{
	projectileId = projectileId_G;
}

unsigned long long int Projectile::projectileId_G = 0;
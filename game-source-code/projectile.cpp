#include "projectile.h"

Projectile::Projectile():
	initialXpos{0.0f},
	initialYpos{0.0f},
	projectileSpeed{ 0.0f },
	xPosition{ 00.0f },
	yPosition{ -100.0f },
	targetXpos{ 0.0f },
	targetYpos{ 0.0f },
	frame_counter{0},
	slope{0.0f},
	yIntercept{0.0f},
	projectileId{0}
{}

Projectile::Projectile(const float x, const float y, const std::string _direction, const float horizontalOffset,
	const float verticalOffset,const float _targetXpos, const float _targetYpos, unsigned long long int _projectileId,
	ProjectileType _typeOfShooter):
	projectileSpeed{ 0.0f }
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

	projectileSpeed = 600.0f;

	targetXpos = _targetXpos;
	if (_typeOfShooter == ProjectileType::Laser) { targetYpos = initialYpos; }
	else { targetYpos = _targetYpos; }
	
	projectileId = _projectileId;
	typeOfShooter = _typeOfShooter;
	calculateTrajectoryConstants();
}

std::string Projectile::getProjectileDirection() const
{
	return direction;
}

std::tuple<float, float> Projectile::getProjectilePosition() const
{
	return { xPosition, yPosition };
}

float Projectile::getProjectileSpeed() const
{
	return projectileSpeed;
}

void Projectile::updateFrameCounter()
{
	++frame_counter;
	if (frame_counter > 20)
	{
		frame_counter = 0;
	}
}

int Projectile::getFrameCounter() const
{
	return frame_counter;
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
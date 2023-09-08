#include "shooter.h"

Shooter::Shooter():
	xPosition{00.0f},
	yPosition{-100.0f},
	projectileSpeed{0.0f}
{}

Shooter::Shooter(const float& x, const float& y, const std::string _direction, const float& horizontalOffset,
	const float& verticalOffset)
{
	direction = _direction;
	yPosition = y + verticalOffset;

	if (direction == "right")
	{
		xPosition = x + horizontalOffset;
	}

	if (direction == "left")
	{
		xPosition = x - horizontalOffset;
	}

	projectileSpeed = 600.0f;
}

void Shooter::updateProjectile(const float& dt)
{
	if (direction == "right")
	{
		xPosition += projectileSpeed * dt;
	}

	if (direction == "left")
	{
		xPosition -= projectileSpeed * dt;
	}
}

std::tuple<float, float> Shooter::getProjectilePosition() const
{
	return { xPosition, yPosition };
}

void Shooter::createProjectile(std::shared_ptr<Shooter>& projectile)
{
	projectiles.push_back(projectile);
}

void Shooter::updateProjectileCoordinates(const float& x, const float& y)
{
	xPosition = x;
	yPosition = y;
}

void Shooter::setProjectileDirection(const std::string& _direction)
{
	direction = _direction;
}

std::string Shooter::getProjectileDirection() const
{
	return direction;
}
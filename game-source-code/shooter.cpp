#include "shooter.h"

Shooter::Shooter():
	xPosition{00.0f},
	yPosition{-100.0f},
	projectileSpeed{0.0f}
{}

Shooter::Shooter(const float& x, const float& y, const std::string _direction)
{
	direction = _direction;
	yPosition = y;

	if (direction == "right")
	{
		xPosition = x + 75.0f;
	}

	if (direction == "left")
	{
		xPosition = x - 75.0f;
	}

	projectileSpeed = 350.0f;
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
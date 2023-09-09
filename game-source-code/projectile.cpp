#include "projectile.h"

Projectile::Projectile():
	initialXpos{0.0f},
	initialYpos{0.0f},
	projectileSpeed{ 0.0f },
	xPosition{ 00.0f },
	yPosition{ -100.0f },
	targetXpos{ 0.0f },
	targetYpos{ 0.0f }
{}

Projectile::Projectile(const float& x, const float& y, const std::string _direction, const float& horizontalOffset,
	const float& verticalOffset,const float _targetXpos, const float _targetYpos):
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
		initialYpos = xPosition;
	}

	projectileSpeed = 600.0f;

	targetXpos = _targetXpos;
	targetYpos = _targetYpos;
}

std::string Projectile::getProjectileDirection() const
{
	return direction;
}

std::tuple<float, float> Projectile::getProjectilePosition() const
{
	return { xPosition, yPosition };
}

void Projectile::updatePosition(const float x, const float y)
{
	xPosition = x;
	yPosition = y;
}

float Projectile::getProjectileSpeed() const
{
	return projectileSpeed;
}

std::tuple<float, float> Projectile::getTargetPosition() const
{
	return{ targetXpos, targetYpos };
}

std::tuple<float, float> Projectile::getInitialProjectilePosition() const
{
	return { initialXpos, initialYpos };
}

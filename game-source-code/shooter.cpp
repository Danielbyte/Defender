#include "shooter.h"

Shooter::Shooter(){}

void Shooter::updateProjectile(float dt)
{
	if (projectiles.empty())
		return;

	auto projectile_iter = projectiles.begin();
	while (projectile_iter != projectiles.end())
	{
		auto direction = (*projectile_iter)->getProjectileDirection();
		auto [xPosition, yPosition] = (*projectile_iter)->getProjectilePosition();
		auto projectileSpeed = (*projectile_iter)->getProjectileSpeed();

		if (direction == "right")
		{
			xPosition += projectileSpeed * dt;
			(*projectile_iter)->updatePosition(xPosition, yPosition);
		}

		if (direction == "left")
		{
			xPosition -= projectileSpeed * dt;
			(*projectile_iter)->updatePosition(xPosition, yPosition);
		}
		++projectile_iter;
	}

}

void Shooter::createProjectile(std::shared_ptr<Projectile>& projectile)
{
	projectiles.push_back(projectile);
}

std::vector<std::shared_ptr<Projectile>> Shooter::getProjectiles()
{
	return projectiles;
}
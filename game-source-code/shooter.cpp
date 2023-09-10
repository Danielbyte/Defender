#include "shooter.h"

Shooter::Shooter(){}

void Shooter::updateProjectile(float dt)
{
	if (projectiles.empty())
		return;

	//Avoid glitches in game
	if (dt > 0.017f)
		dt = 1 / 60.0f;

	auto missile_iter = projectiles.begin();

	while (missile_iter != projectiles.end())
	{
		auto _direction = (*missile_iter)->getProjectileDirection();

		if (_direction == "left")
		{
			auto [x, y] = (*missile_iter)->getProjectilePosition();
			auto speed = (*missile_iter)->getSpeed();
			auto newX = x - speed * dt;
			(*missile_iter)->updateTrajectory(newX);
		}

		if (_direction == "right")
		{
			auto [x, y] = (*missile_iter)->getProjectilePosition();
			auto speed = (*missile_iter)->getSpeed();
			auto newX = x + speed * dt;
			(*missile_iter)->updateTrajectory(newX);
		}
		++missile_iter;
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

std::vector<std::shared_ptr<Projectile>> Shooter::projectiles;
#include "shooter.h"

Shooter::Shooter(){}

void Shooter::updateProjectile(float dt, const ProjectileType type)
{
	if (projectiles.empty())
		return;

	auto projectile_iter = projectiles.begin();

	while (projectile_iter != projectiles.end())
	{
		if ((*projectile_iter)->getType() == type)
		{
			auto _direction = (*projectile_iter)->getProjectileDirection();

			if (_direction == "left")
			{
				auto [x, y] = (*projectile_iter)->getProjectilePosition();
				auto speed = (*projectile_iter)->getSpeed();
				auto newX = x - speed * dt;
				(*projectile_iter)->updateTrajectory(newX);
			}

			if (_direction == "right")
			{
				auto [x, y] = (*projectile_iter)->getProjectilePosition();
				auto speed = (*projectile_iter)->getSpeed();
				auto newX = x + speed * dt;
				(*projectile_iter)->updateTrajectory(newX);
			}
		}
		++projectile_iter;
	}
}

void Shooter::updateProjectile(const float dt, std::vector<std::shared_ptr<Projectile>>& projectile)
{
	if (projectile.empty())
		return;

	auto projectile_iter = projectile.begin();

	while (projectile_iter != projectile.end())
	{
			auto _direction = (*projectile_iter)->getProjectileDirection();
			if (_direction == "left")
			{
				auto [x, y] = (*projectile_iter)->getProjectilePosition();
				auto speed = (*projectile_iter)->getSpeed();
				auto newX = x - speed * dt;
				(*projectile_iter)->updateTrajectory(newX);
			}

			if (_direction == "right")
			{
				auto [x, y] = (*projectile_iter)->getProjectilePosition();
				auto speed = (*projectile_iter)->getSpeed();
				auto newX = x + speed * dt;
				(*projectile_iter)->updateTrajectory(newX);
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

//function to update projectile Ids once a projectile has been deleted
void Shooter::updateIds()
{
	auto projectile_iter = projectiles.begin();
	while (projectile_iter != projectiles.end())
	{
		if (projectile_iter == projectiles.begin())
		{
			(*projectile_iter)->setNewId(0);
			++projectile_iter;
		}

		else
		{
			auto newId = (*(projectile_iter - 1))->getProjectileId() + 1;
			(*projectile_iter)->setNewId(newId);
			++projectile_iter;
		}
	}
}

void Shooter::deleteProjectile(unsigned long long int Id)
{
	auto projectile_iter = projectiles.begin();

	while (projectile_iter != projectiles.end())
	{
		auto ID = (*projectile_iter)->getProjectileId();

		if (ID == Id)
		{
			projectiles.erase(projectile_iter);
		}
		else
		{
			++projectile_iter;
		}
	}
}

std::vector<std::shared_ptr<Projectile>> Shooter::projectiles;
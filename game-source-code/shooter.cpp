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
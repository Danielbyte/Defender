#include "shooter.h"

Shooter::Shooter(){}

void Shooter::updateProjectile(float dt, const ProjectileType type,
	std::vector<std::shared_ptr<MissileSprite>>& missile_sprites)
{
	if (projectiles.empty())
		return;

	auto projectile_iter = projectiles.begin();
	auto missile_sprite = missile_sprites.begin();

	while (projectile_iter != projectiles.end())
	{
		auto _direction = (*projectile_iter)->getProjectileDirection();
		if (_direction == "left")
		{
			auto [x, y] = (*projectile_iter)->getProjectilePosition();
			auto speed = (*projectile_iter)->getSpeed();
			auto newX = x - speed * dt;
			(*projectile_iter)->updateTrajectory(newX);

			auto [xPos, yPos] = (*projectile_iter)->getProjectilePosition();

			if (yPos <= 100.0f)
			{
				(*missile_sprite)->remove();
			}

		}

		if (_direction == "right")
		{
			auto [x, y] = (*projectile_iter)->getProjectilePosition();
			auto speed = (*projectile_iter)->getSpeed();
			auto newX = x + speed * dt;
			(*projectile_iter)->updateTrajectory(newX);

			auto [xPos, yPos] = (*projectile_iter)->getProjectilePosition();

			if (yPos <= 100.0f)
			{
				(*missile_sprite)->remove();
			}
		}
		
		++projectile_iter;
		++missile_sprite;
	}

	projectile_iter = projectiles.begin();
	missile_sprite = missile_sprites.begin();
	while (missile_sprite != missile_sprites.end())
	{
		if ((*missile_sprite)->needsDeletion())
		{
			deleteProjectile((*projectile_iter)->getProjectileId());
			missile_sprites.erase(missile_sprite);
		}
		else
		{
			++missile_sprite;
			++projectile_iter;
		}
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
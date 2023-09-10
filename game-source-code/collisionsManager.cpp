#include "collisionsManager.h"

CollisionsManager::CollisionsManager():
playerWidth{20.0f},
playerLength{50.0f},
landerWidth{16.0f},
landerLength{16.0f},
missileWidth{6.0f},
missileLength{6.0f}
{}

void CollisionsManager::playerLanderCollisions(std::shared_ptr<Player>& player, std::vector<std::shared_ptr<Lander>>& landers,
	std::vector<std::shared_ptr<LanderSprite>>& lander_sprites)
{
	if (landers.empty())
		return;

	auto lander_iter = landers.begin();
	auto lander_sprite_iter = lander_sprites.begin();
	auto [playerXpos, playerYpos] = player->getPlayerPosition();
	
	while (lander_iter != landers.end())
	{
		auto [landerXpos, landerYpos] = (*lander_iter)->getPosition();
		
		auto isColiided = collisions.checkCollision(playerXpos, playerYpos, playerWidth, playerLength, landerXpos,
			landerYpos, landerWidth, landerLength);

		if (isColiided)
		{
			std::cout << "player-lander collision!" << std::endl;
			//should set game over to true
		}
		
			++lander_iter;
			++lander_sprite_iter;
	}
}

void CollisionsManager::playerMissileCollisions(std::shared_ptr<Player>& player, std::vector<std::shared_ptr<Lander>>& landers,
	std::vector<std::shared_ptr<MissileSprite>>& missile_sprites)
{
	if (missile_sprites.empty())
		return;

	std::shared_ptr<Shooter>shooter_obj = std::make_shared<Shooter>();
	auto _projectiles = shooter_obj->getProjectiles();

	auto [playerXpos, playerYpos] = player->getPlayerPosition();

	auto projectile_iter = _projectiles.begin();
	auto missile_sprite_iter = missile_sprites.begin();

	while (projectile_iter != _projectiles.end())
	{
		//Update w.r.t lander missiles only, else skip
		if ((*projectile_iter)->getType() == ProjectileType::LanderMissile)
		{
			auto [missileXpos, missileYpos] = (*projectile_iter)->getProjectilePosition();

			auto isCollided = collisions.checkCollision(playerXpos, playerYpos, playerWidth, playerLength, missileXpos,
				missileYpos, missileWidth, missileLength);

			if (isCollided)
			{
				auto Id = (*projectile_iter)->getProjectileId();
				shooter_obj->deleteProjectile(Id);
				missile_sprites.erase(missile_sprite_iter);
				_projectiles.erase(projectile_iter);
			}
			else
			{
				++projectile_iter;
				++missile_sprite_iter;
			}
		}
		else
		{
			++projectile_iter;
		}
	}
}
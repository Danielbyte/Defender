#include "collisionsManager.h"

CollisionsManager::CollisionsManager():
playerWidth{20.0f},
playerLength{50.0f},
landerWidth{16.0f},
landerLength{16.0f},
missileWidth{6.0f},
missileLength{6.0f},
laserWidth{2.0f},
laserLength{100.0f},
humanoidWidth{6.0f},
humanoidLength{16.0f}
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

void CollisionsManager::playerAndMissileCollisions(std::shared_ptr<Player>& player,
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
				shooter_obj->updateIds();
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

void CollisionsManager::landerAndLaserCollisions(std::vector<std::shared_ptr<Lander>>& landers,
	std::vector<std::shared_ptr<LanderSprite>>& lander_sprites, std::vector<std::shared_ptr<LaserSprite>>& laser_sprites)
{
	if (landers.empty())
		return;

	std::shared_ptr<Shooter> shooter_obj = std::make_shared<Shooter>();
	auto _projectiles = shooter_obj->getProjectiles();
	auto laser_sprite = laser_sprites.begin();
	
	auto projectile_iter = _projectiles.begin();

	while (projectile_iter != _projectiles.end())
	{
		if ((*projectile_iter)->getType() == ProjectileType::Laser)
		{
			auto lander_obj = landers.begin();
			auto lander_sprite = lander_sprites.begin();
			auto hadAcollision = false;
			while (lander_obj != landers.end())
			{
				auto [landerXpos, landerYpos] = (*lander_obj)->getPosition();
				auto [laserXpos, laserYpos] = (*projectile_iter)->getProjectilePosition();


			    auto isCollided = collisions.checkCollision(landerXpos, landerYpos, landerWidth, landerLength,laserXpos,
					laserYpos, laserWidth, laserLength);
				
				if (isCollided)
				{
					landers.erase(lander_obj);
					lander_sprites.erase(lander_sprite);
					(*laser_sprite)->remove();
					shooter_obj->deleteProjectile((*projectile_iter)->getProjectileId());
					shooter_obj->updateIds();
					_projectiles.erase(projectile_iter);
					hadAcollision = true;
				}
				else
				{
					++lander_obj;
					++lander_sprite;
				}
			}

			if (!hadAcollision) { ++projectile_iter; }
			++laser_sprite;
		}

		else
		{
			++projectile_iter;
		}
	}
	
	laser_sprite = laser_sprites.begin();
	while (laser_sprite != laser_sprites.end())
	{
		if ((*laser_sprite)->needsDeletion())
		{
			laser_sprites.erase(laser_sprite);
		}
		else
		{
			++laser_sprite;
		}
	}
}

void CollisionsManager::landerAndHumanoidCollisions(std::vector<std::shared_ptr<Lander>>& landers,
	std::vector<std::shared_ptr<Humanoid>>& humanoids)
{
	for (auto& lander : landers)
	{
		for (auto& humanoid : humanoids)
		{
			auto humanoid_state = humanoid->getHumanoidState();
			switch (humanoid_state)
			{
			case HumanoidState::Walking:
				setAbductionStates(lander, humanoid);
				break;
			case HumanoidState::Abducted:
				break;
			case HumanoidState::Falling:
				break;
			default:
				break;
			}
		}
	}
}

void CollisionsManager::setAbductionStates(std::shared_ptr<Lander>& lander, std::shared_ptr<Humanoid>& humanoid)
{
	auto [humanoidXpos, humanoidYpos] = humanoid->getPosition();
	auto [landerXpos, landerYpos] = lander->getPosition();

	auto isCollided = collisions.checkCollision(humanoidXpos, humanoidYpos, humanoidWidth, humanoidLength,
		landerXpos, landerYpos, landerWidth, landerLength);

	if (isCollided)
	{
		lander->setToascend();
		humanoid->setToAbducted();
	}
}
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
humanoidLength{16.0f},
groundLevel{580.0f},
bomberWidth{20.0f},
bomberLength{20.0f}
{}

void CollisionsManager::playerLanderCollisions(std::shared_ptr<Player>& player, std::vector<std::shared_ptr<Lander>>& landers,
	std::vector<std::shared_ptr<LanderSprite>>& lander_sprites)
{
	PlayerState state = player->getPlayerState();
	if (state == PlayerState::Dead)
		return;

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
			player->restartAnimationWatch();
			player->setPlayerState(PlayerState::Dead);
		}
		
			++lander_iter;
			++lander_sprite_iter;
	}
}

void CollisionsManager::playerAndMissileCollisions(std::shared_ptr<Player>& player,
	std::vector<std::shared_ptr<MissileSprite>>& missile_sprites)
{
	PlayerState state = player->getPlayerState();

	if (state == PlayerState::Dead)
		return;

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
				player->restartAnimationWatch();
				player->setPlayerState(PlayerState::Dead);
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
	std::vector<std::shared_ptr<LanderSprite>>& lander_sprites, std::vector<std::shared_ptr<LaserSprite>>& laser_sprites,
	std::vector<std::shared_ptr<Projectile>>& lasers, std::vector<std::shared_ptr<Humanoid>>& humanoids, int& landersDestroyed)
{
	if (landers.empty())
		return;

	auto laser_sprite = laser_sprites.begin();
	auto laser = lasers.begin();

	while (laser != lasers.end())
	{
		auto lander_sprite = lander_sprites.begin();
		auto lander = landers.begin();
		while (lander != landers.end())
		{
			auto [landerXpos, landerYpos] = (*lander)->getPosition();
			auto [laserXpos, laserYpos] = (*laser)->getProjectilePosition();

			auto isCollided = collisions.checkCollision(landerXpos, landerYpos, landerWidth, landerLength,
				laserXpos, laserYpos, laserWidth, laserLength);

			if (isCollided)
			{
				landers.erase(lander);
				lander_sprites.erase(lander_sprite);
				(*laser_sprite)->remove();
				++landersDestroyed;
			}
			else
			{
				++lander;
				++lander_sprite;
			}
		}
		++laser_sprite;
		++laser;
	}
	
	laser_sprite = laser_sprites.begin();
	laser = lasers.begin();
	while (laser_sprite != laser_sprites.end())
	{
		if ((*laser_sprite)->needsDeletion())
		{
			laser_sprites.erase(laser_sprite);
			lasers.erase(laser);
		}
		else
		{
			++laser_sprite;
			++laser;
		}
	}

	for (auto& humanoid : humanoids)
	{
		if (humanoid->getHumanoidState() == HumanoidState::Abducted)
		dropHumanoid(humanoid, landers);
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
				//checkStateOfAbductingLander(humanoid, isCollided);
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
		humanoid->setAbductingLanderId(lander->getLocalId()); //reference to the abducting id
	}
}

void CollisionsManager::dropHumanoid(std::shared_ptr<Humanoid>& humanoid, std::vector<std::shared_ptr<Lander>>& landers)
{
	//If player shoot lander which is in the process of abducting a humanoid, the humanoid will begin to fall
	auto id = humanoid->getAbductingLanderId();
	for (auto& lander : landers)
	{
		if (id == lander->getLocalId())
			return;
	}

	humanoid->setHumanoidState(HumanoidState::Falling);
}

void CollisionsManager::playerAndFallingHumanoidCollisions(std::shared_ptr<Player>& player,
	std::vector<std::shared_ptr<Humanoid>>& humanoids, std::vector<std::shared_ptr<HumanoidSprite>>& humanoid_sprites)
{
	auto humanoid_sprite = humanoid_sprites.begin();

	for (auto& humanoid : humanoids)
	{
		auto [humanoidXpos, humanoidYpos] = humanoid->getPosition();
		auto [playerXpos, playerYpos] = player->getPlayerPosition();

		auto isCollided = collisions.checkCollision(playerXpos, playerYpos, playerWidth, playerLength, humanoidXpos,
			humanoidYpos, humanoidWidth, humanoidLength);

		if (isCollided)
		{
			if (humanoid->getHumanoidState() == HumanoidState::Falling)
				humanoid->setHumanoidState(HumanoidState::Rescued);

			if (humanoid->getHumanoidState() == HumanoidState::Rescued)
			{
				auto distanceBetween = abs(playerXpos - humanoidXpos);
				humanoid->setDistance(distanceBetween);
			}
		
		}
		++humanoid_sprite;
	}
}

void CollisionsManager::humanoidAndGroundCollisions(std::vector<std::shared_ptr<Humanoid>>& humanoids,
	std::vector<std::shared_ptr<HumanoidSprite>>& humanoid_sprites)
{
	auto humanoid_sprite = humanoid_sprites.begin();
	auto humanoid = humanoids.begin();
	while (humanoid != humanoids.end())
	{
		auto [xHumanoidPos, yHumanoidPos] = (*humanoid)->getPosition();
		auto humanoidDead = false;

		if (yHumanoidPos >= groundLevel)
		{
			auto humanoidState = (*humanoid)->getHumanoidState();
			switch (humanoidState)
			{
			case HumanoidState::Falling:
				(*humanoid)->setHumanoidState(HumanoidState::Dead);
				humanoid_sprites.erase(humanoid_sprite);
				humanoids.erase(humanoid);
				humanoidDead = true;
				break;

			case HumanoidState::Rescued:
				(*humanoid)->setHumanoidState(HumanoidState::Walking);
				break;

			default:
				break;
			}

			if (!humanoidDead) { ++humanoid; ++humanoid_sprite; }
		}
		else
		{
			++humanoid;
			++humanoid_sprite;
		}
	}
}

void CollisionsManager::playerLaserAndHumanoidCollisions(std::vector<std::shared_ptr<Humanoid>>& humanoids,
	std::vector<std::shared_ptr<HumanoidSprite>>& humanoid_sprites, 
	std::vector<std::shared_ptr<LaserSprite>>& laser_sprites, std::vector<std::shared_ptr<Projectile>>& lasers)
{
	auto laser_sprite = laser_sprites.begin();
	auto projectile = lasers.begin();

	while (projectile != lasers.end())
	{
		auto humanoid = humanoids.begin();
		auto humanoid_sprite = humanoid_sprites.begin();
		auto erasedProjectile = false;
		while (humanoid != humanoids.end())
		{
			auto [humanoidXpos, humanoidYpos] = (*humanoid)->getPosition();
			auto [laserXpos, laserYpos] = (*projectile)->getProjectilePosition();

			auto isCollided = collisions.checkCollision(humanoidXpos, humanoidYpos, humanoidWidth, humanoidLength,
				laserXpos, laserYpos, laserWidth, laserLength);

			auto humanoidState = (*humanoid)->getHumanoidState();
			if (isCollided && humanoidState == HumanoidState::Abducted)
			{
				(*laser_sprite)->remove();
				humanoids.erase(humanoid);
				humanoid_sprites.erase(humanoid_sprite);
			}
			else
			{
				++humanoid;
				++humanoid_sprite;
			}

		}
		++laser_sprite;
		++projectile;
	}

	laser_sprite = laser_sprites.begin();
	projectile = lasers.begin();
	while (laser_sprite != laser_sprites.end())
	{
		if ((*laser_sprite)->needsDeletion())
		{
			laser_sprites.erase(laser_sprite);
			lasers.erase(projectile);
		}
		else
		{
			++laser_sprite;
			++projectile;
		}
	}
}

void CollisionsManager::LaserAndBomberCollisions(std::vector<std::shared_ptr<Bombers>>& bombers, std::vector<std::shared_ptr<BomberSprite>>& bomber_sprites,
	std::vector<std::shared_ptr<Projectile>>& lasers, std::vector<std::shared_ptr<LaserSprite>>& laser_sprites)
{

	auto laser = lasers.begin();
	auto laser_sprite = laser_sprites.begin();

	while (laser != lasers.end())
	{
		auto bomber = bombers.begin();
		auto bomber_sprite = bomber_sprites.begin();
		while (bomber != bombers.end())
		{
			auto [laserXpos, laserYpos] = (*laser)->getProjectilePosition();
			auto [bomberXpos, bomberYpos] = (*bomber)->getPosition();

			auto isCollided = collisions.checkCollision(laserXpos, laserYpos, laserWidth, laserLength, 
				bomberXpos, bomberYpos, bomberWidth, bomberLength);

			if (isCollided)
			{
				bombers.erase(bomber);
				bomber_sprites.erase(bomber_sprite);
				(*laser_sprite)->remove();
			}
			else
			{
				++bomber;
				++bomber_sprite;
			}
		}
		++laser;
		++laser_sprite;
	}

	laser_sprite = laser_sprites.begin();
	laser = lasers.begin();

	while (laser_sprite != laser_sprites.end())
	{
		if ((*laser_sprite)->needsDeletion())
		{
			lasers.erase(laser);
			laser_sprites.erase(laser_sprite);
		}
		else
		{
			++laser;
			++laser_sprite;
		}
	}
}
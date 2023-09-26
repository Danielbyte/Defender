#include "game.h"

void Game::updateGame(const float dt)
{
	if (!isPlaying)
		return;

	

	updateHumanoids(dt);

	player_obj->updatePlayer(leftPressed, rightPressed, upPressed, downPressed,spacePressed,player_sprite,
		laser_sprite,dt);

	game_world->updateGameWorld(lander_objects, lander_object_sprites, player_obj);

	if (!lander_objects.empty())
		updateLanders(dt);

	updateProjectiles(dt);
	updateCollisions();
}

void Game::updateLanders(const float dt)
{
	auto object_iter = lander_objects.begin();
	auto sprite_iter = lander_object_sprites.begin();
	while (object_iter != lander_objects.end())
	{
		(*object_iter)->updateLander(*sprite_iter,dt,player_obj,lander_missile_sprites,humanoid_objects);
		++object_iter;
		++sprite_iter;
	}
}

void Game::updateCollisions()
{
	update_collisions.playerLanderCollisions(player_obj, lander_objects, lander_object_sprites);
	update_collisions.playerAndMissileCollisions(player_obj, lander_missile_sprites);
	update_collisions.landerAndLaserCollisions(lander_objects, lander_object_sprites, laser_sprite,humanoid_objects);
	update_collisions.landerAndHumanoidCollisions(lander_objects, humanoid_objects);
	update_collisions.playerAndFallingHumanoidCollisions(player_obj, humanoid_objects,humanoid_sprites);
	update_collisions.humanoidAndGroundCollisions(humanoid_objects,humanoid_sprites);
	update_collisions.playerLaserAndHumanoidCollisions(humanoid_objects, humanoid_sprites, laser_sprite);
}

void Game::updateHumanoids(const float dt)
{
	auto humanoid_sprite = humanoid_sprites.begin();
	auto humanoid = humanoid_objects.begin();
	while (humanoid != humanoid_objects.end())
	{
		(*humanoid)->updateHumanoid(dt, *humanoid_sprite,player_obj);
		++humanoid;
		++humanoid_sprite;
	}
}

void Game::updateProjectiles(const float dt)
{
	std::shared_ptr<Lander>lander_object = std::make_shared<Lander>();
	lander_object->updateMissileSprites(lander_missile_sprites);
	
	if (lander_objects.empty())
	shooter_object->updateProjectile(dt,ProjectileType::LanderMissile);
}
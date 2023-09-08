#include "game.h"

void Game::updateGame(const float dt)
{
	if (!isPlaying)
		return;

	game_world->updateGameWorld(lander_objects, lander_object_sprites);

	player_obj->updatePlayer(leftPressed, rightPressed, upPressed, downPressed,spacePressed,player_sprite,
		laser_sprite,dt);

	if (!lander_objects.empty())
		updateLanders(dt);
}

void Game::updateLanders(const float dt)
{
	auto object_iter = lander_objects.begin();
	auto sprite_iter = lander_object_sprites.begin();
	while (object_iter != lander_objects.end())
	{
		(*object_iter)->updateLander(*sprite_iter,dt,player_obj,missile_sprites);
		++object_iter;
		++sprite_iter;
	}
}
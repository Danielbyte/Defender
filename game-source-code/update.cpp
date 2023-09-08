#include "game.h"

void Game::updateGame(const float dt)
{
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
		(*object_iter)->updateLander(*sprite_iter,dt);
		++object_iter;
		++sprite_iter;
	}
}
#include "game.h"

void Game::updateGame(const float dt)
{
	player_obj->updatePlayer(leftPressed, rightPressed, upPressed, downPressed);
}
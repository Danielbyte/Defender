#include "collisionsManager.h"

CollisionsManager::CollisionsManager():
playerWidth{20.0f},
playerLength{50.0f},
landerWidth{16.0f},
landerLength{16.0f}
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

void playerMissileCollisions(std::shared_ptr<Player>& player, std::vector<std::shared_ptr<Lander>>& landers,
	std::vector<std::shared_ptr<MissileSprite>>& missile_sprites)
{
	if (landers.empty())
		return;

	auto lander_iter = landers.begin();
	auto missile_sprite_iter = missile_sprites.begin();

	while (lander_iter != landers.end())
	{
		++lander_iter;
		++missile_sprite_iter;
	}
}
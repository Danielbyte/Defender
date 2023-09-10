#ifndef COLLISIONSMANAGER_H
#define COLLISIONSMANAGER_H

#include "collisions.h"
#include "player.h"
#include "lander.h"

class CollisionsManager
{
public:
	CollisionsManager();
	void playerLanderCollisions(std::shared_ptr<Player>& player, std::vector<std::shared_ptr<Lander>>& landers,
		std::vector<std::shared_ptr<LanderSprite>>& lander_sprites);

	void playerMissileCollisions(std::shared_ptr<Player>& player, std::vector<std::shared_ptr<Lander>>& landers,
		std::vector<std::shared_ptr<MissileSprite>>& missile_sprites);

private:
	float playerWidth, playerLength;
	float landerWidth, landerLength;
	float missileWidth, missileLength;
	Collisions collisions;

};
#endif // !COLLISIONSMANAGER_H


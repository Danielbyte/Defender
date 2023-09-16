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

	void playerAndMissileCollisions(std::shared_ptr<Player>& player,
		std::vector<std::shared_ptr<MissileSprite>>& missile_sprites);

	void landerAndLaserCollisions(std::vector<std::shared_ptr<Lander>>& landers,
		std::vector<std::shared_ptr<LanderSprite>>& lander_sprites,
		std::vector<std::shared_ptr<LaserSprite>>& laser_sprites, std::vector<std::shared_ptr<Humanoid>>& humanoids);

	void landerAndHumanoidCollisions(std::vector<std::shared_ptr<Lander>>& landers,
		std::vector<std::shared_ptr<Humanoid>>& humanoids);

	void playerAndFallingHumanoidCollisions(std::shared_ptr<Player>& player,
		std::vector<std::shared_ptr<Humanoid>>& humanoids,std::vector<std::shared_ptr<HumanoidSprite>>& humanoid_sprites);

	void humanoidAndGroundCollisions(std::vector<std::shared_ptr<Humanoid>>& humanoids);

private:
	void setAbductionStates(std::shared_ptr<Lander>& lander, std::shared_ptr<Humanoid>& humanoid);

	void dropHumanoid(std::shared_ptr<Humanoid>& humanoid, std::vector<std::shared_ptr<Lander>>& landers);

	float playerWidth, playerLength;
	float landerWidth, landerLength;
	float missileWidth, missileLength;
	float laserWidth, laserLength;
	float humanoidWidth, humanoidLength;
	float groundLevel;
	Collisions collisions;

};
#endif // !COLLISIONSMANAGER_H


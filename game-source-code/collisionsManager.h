#ifndef COLLISIONSMANAGER_H
#define COLLISIONSMANAGER_H

#include "collisions.h"
#include "player.h"
#include "lander.h"
#include "bombers.h"

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
		std::vector<std::shared_ptr<LaserSprite>>& laser_sprites,
		std::vector<std::shared_ptr<Projectile>>& lasers, std::vector<std::shared_ptr<Humanoid>>& humanoids,
		int& landersDestroyed);

	void landerAndHumanoidCollisions(std::vector<std::shared_ptr<Lander>>& landers,
		std::vector<std::shared_ptr<Humanoid>>& humanoids);

	void playerAndFallingHumanoidCollisions(std::shared_ptr<Player>& player,
		std::vector<std::shared_ptr<Humanoid>>& humanoids,std::vector<std::shared_ptr<HumanoidSprite>>& humanoid_sprites);

	void humanoidAndGroundCollisions(std::vector<std::shared_ptr<Humanoid>>& humanoids,
		std::vector<std::shared_ptr<HumanoidSprite>>& humanoid_sprites);

	void playerLaserAndHumanoidCollisions(std::vector<std::shared_ptr<Humanoid>>& humanoids,
		std::vector<std::shared_ptr<HumanoidSprite>>& humanoid_sprites, 
		std::vector<std::shared_ptr<LaserSprite>>& laser_sprites, std::vector<std::shared_ptr<Projectile>>& lasers);

	void LaserAndBomberCollisions(std::vector<std::shared_ptr<Bombers>>& bombers, std::vector<std::shared_ptr<BomberSprite>>& bomber_sprites,
		std::vector<std::shared_ptr<Projectile>>& lasers, std::vector<std::shared_ptr<LaserSprite>>& laser_sprites);

	void MineAndPlayerCollisions(std::vector<std::shared_ptr<Mine>>& mines, std::vector<std::shared_ptr<MineSprite>>& mine_sprites,
		std::shared_ptr<Player>& player);

private:
	void setAbductionStates(std::shared_ptr<Lander>& lander, std::shared_ptr<Humanoid>& humanoid);

	void dropHumanoid(std::shared_ptr<Humanoid>& humanoid, std::vector<std::shared_ptr<Lander>>& landers);

	float playerWidth, playerLength;
	float landerWidth, landerLength;
	float missileWidth, missileLength;
	float laserWidth, laserLength;
	float humanoidWidth, humanoidLength;
	float groundLevel;
	float bomberWidth, bomberLength;
	float mineWidth, mineLength;
	Collisions collisions;

};
#endif // !COLLISIONSMANAGER_H


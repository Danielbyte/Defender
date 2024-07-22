#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <iostream>
#include "lander.h"
#include "humanoidSprite.h"
#include "humanoid.h"
#include "landscape.h"
#include "landscapeSprite.h"
#include "bombers.h"
#include "bomberSprite.h"

enum class Enemy{Lander,Bomber,Pod,None};

class GameWorld
{
public:
	GameWorld();

	void updateGameWorld(std::vector<std::shared_ptr<Lander>>& lander_objects,
		std::vector<std::shared_ptr<LanderSprite>>& lander_object_sprites, std::shared_ptr<Player>& player,
		std::vector<std::shared_ptr<MissileSprite>>& missile_sprites, std::vector<std::shared_ptr<Bombers>>& bombers,
		std::vector<std::shared_ptr<BomberSprite>>& bomber_sprites);

	Enemy generateEnemy();

	void placeHumanoids(std::vector<std::shared_ptr<Humanoid>>& humanoid_objects,
		std::vector<std::shared_ptr<HumanoidSprite>>& humanoid_sprites, float horizontalScalingFactor, float verticalScalingFactor);

private:
	std::shared_ptr<Shooter> shooter_obj = std::make_shared<Shooter>();
	std::shared_ptr<StopWatch> world_watch = std::make_shared<StopWatch>();
	std::shared_ptr<Landscape> landscape_object = std::make_shared<Landscape>();
	Enemy enemy;
	bool initialization;
	void initialLanders(std::shared_ptr<Player>& player,std::vector<std::shared_ptr<Lander>>& lander_objects, std::vector<std::shared_ptr<LanderSprite>>& lander_sprites);

	void createLander(std::vector<std::shared_ptr<Lander>>& lander_objects,
		std::vector<std::shared_ptr<LanderSprite>>& lander_object_sprites, std::shared_ptr<Player>& player);

	void createBomber(std::vector<std::shared_ptr<Bombers>>& bombers,
		std::vector<std::shared_ptr<BomberSprite>>& bomber_sprites, std::shared_ptr<Player>& player);
    
	void garbageCollector(std::vector<std::shared_ptr<MissileSprite>>& missile_sprites);
	std::shared_ptr<StopWatch> lander_watch = std::make_shared<StopWatch>();//stop watch used for creation of landers

	void placeHumanoid(std::vector<std::shared_ptr<Humanoid>>& humanoid_objects, std::vector<std::shared_ptr<HumanoidSprite>>&
		humanoid_sprites, float xPos, float yPos);
};
#endif // !GAMEWORLD_H


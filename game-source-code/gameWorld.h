#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <iostream>
#include "lander.h"
#include "humanoidSprite.h"
#include "humanoid.h"
#include <set>

enum class Enemy{Lander,Bomber,Pod,None};

class GameWorld
{
public:
	GameWorld();

	void updateGameWorld(std::vector<std::shared_ptr<Lander>>& lander_objects,
		std::vector<std::shared_ptr<LanderSprite>>& lander_object_sprites);

	Enemy generateEnemy();

	void placeHumanoids(std::vector<std::shared_ptr<Humanoid>>& humanoid_objects,
		std::vector<std::shared_ptr<HumanoidSprite>>& humanoid_sprites);

private:
	std::shared_ptr<StopWatch> world_watch = std::make_shared<StopWatch>();
	Enemy enemy;

	void createLander(std::vector<std::shared_ptr<Lander>>& lander_objects,
		std::vector<std::shared_ptr<LanderSprite>>& lander_object_sprites);
};
#endif // !GAMEWORLD_H


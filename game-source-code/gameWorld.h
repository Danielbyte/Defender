#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include "lander.h"

enum class Enemy{Lander,Bomber,Pod,None};

class GameWorld
{
public:
	GameWorld();
	void updateGameWorld(std::vector<std::shared_ptr<Lander>>& lander_objects,
		std::vector<std::shared_ptr<LanderSprite>>& lander_object_sprites);

private:
	std::shared_ptr<StopWatch> world_watch = std::make_shared<StopWatch>();
	Enemy enemy;
};
#endif // !GAMEWORLD_H


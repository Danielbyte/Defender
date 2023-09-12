#include "gameWorld.h"

GameWorld::GameWorld():
enemy{Enemy::None} //initially, there are no enemies
{}

void GameWorld::updateGameWorld(std::vector<std::shared_ptr<Lander>>& lander_objects,
	std::vector<std::shared_ptr<LanderSprite>>& lander_object_sprites)
{
	auto _time = world_watch->time_elapsed();
	generateEnemy();

	if (_time < 5.0f || enemy ==Enemy::None)
		return;

	switch (enemy)
	{
	case Enemy::Lander:
		createLander(lander_objects, lander_object_sprites);
		break;
	case Enemy::Bomber:
		//std::cout << "Create Bomber" << std::endl;
		break;
	case Enemy::Pod:
		//std::cout << "Create Pod" << std::endl;
		break;
	case Enemy::None:
		//std::cout << "Nothing" << std::endl; //control should never reach here
		break;
	default:
		break;
	}

	world_watch->restart(); //Remove once the other entity creation functions are done
}

Enemy GameWorld::generateEnemy()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	int min = 0;
	int max = 3;
	std::uniform_int_distribution<int>distribution(min, max);
	auto _enemy = distribution(gen);

	if (_enemy == 0)
	{
		enemy = Enemy::Lander;
		return enemy;
	}

	if (_enemy == 1)
	{
		enemy = Enemy::Bomber;
		return enemy;
	}

	if (_enemy == 2)
	{
		enemy = Enemy::Pod;
		return enemy;
	}

	if (_enemy == 3)
	{
		enemy = Enemy::None;
		return enemy;
	}

	return Enemy::None;
}

void GameWorld::createLander(std::vector<std::shared_ptr<Lander>>& lander_objects,
	std::vector<std::shared_ptr<LanderSprite>>& lander_object_sprites)
{
	auto lander_object = std::make_shared<Lander>();
	lander_objects.push_back(lander_object);
	auto lander_sprite = std::make_shared<LanderSprite>();
	lander_object_sprites.push_back(lander_sprite);
	world_watch->restart();
}

void GameWorld::placeHumanoids(std::vector<std::shared_ptr<Humanoid>>& humanoid_objects,
	std::vector<std::shared_ptr<HumanoidSprite>>& humanoid_sprites)
{
	//generate 5 humanoids
	for (int i = 0; i < 4; ++i)
	{
		auto humanoid = std::make_shared<Humanoid>();
		humanoid_objects.push_back(humanoid);
		auto humanoid_sprite = std::make_shared<HumanoidSprite>();
		humanoid_sprites.push_back(humanoid_sprite);
	}
}

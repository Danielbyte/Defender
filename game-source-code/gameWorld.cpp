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
		break;
	case Enemy::Bomber:
		break;
	case Enemy::Pod:
		break;
	case Enemy::None:
		break;
	default:
		break;
	}
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
}

void GameWorld::createLander(std::vector<std::shared_ptr<Lander>>& lander_objects,
	std::vector<std::shared_ptr<LanderSprite>>& lander_object_sprites)
{

}

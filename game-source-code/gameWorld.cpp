#include "gameWorld.h"

GameWorld::GameWorld(std::vector<std::shared_ptr<Humanoid>>& humanoid_objects,
	std::vector<std::shared_ptr<HumanoidSprite>>& humanoid_sprites):
enemy{Enemy::None} //initially, there are no enemies
{
	placeHumanoids(humanoid_objects, humanoid_sprites);
}

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
	std::set<float>existentXpositions;
	float y_position = 50.0f;
	for (int i = 0; i < 4; ++i)
	{
		auto x_position = generateXposition(existentXpositions);
		auto direction = generateDirection();
		std::shared_ptr<Humanoid>humanoid = std::make_shared<Humanoid>(x_position, y_position, direction);
		humanoid_objects.push_back(humanoid);

		std::shared_ptr<HumanoidSprite>humanoid_sp = std::make_shared<HumanoidSprite>();
		humanoid_sprites.push_back(humanoid_sp);
	}
}

float GameWorld::generateXposition(std::set<float>& existentXpositions)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	float min = 4.0f;
	float max = 796.0f;
	std::uniform_real_distribution<float>distribution(min, max);

	float randomXpos;
	do
	{
		randomXpos = distribution(gen);
	} while (existentXpositions.count(randomXpos) > 0);

	return randomXpos;
}

std::string GameWorld::generateDirection()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	int min = 1;
	int max = 10;
	std::uniform_int_distribution<int>distribution(min, max);
	auto direction = distribution(gen);

	if (direction <= 5)
		return "right";

	return "left";
}

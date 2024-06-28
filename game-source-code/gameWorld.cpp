#include "gameWorld.h"

GameWorld::GameWorld():
enemy{Enemy::None}, //initially, there are no enemies
initialization{true} //flag to signal if iinitial game objects have been instantiated
{}

void GameWorld::updateGameWorld(std::vector<std::shared_ptr<Lander>>& lander_objects,
	std::vector<std::shared_ptr<LanderSprite>>& lander_sprites, std::shared_ptr<Player>& player,
	std::vector<std::shared_ptr<MissileSprite>>& missile_sprites, std::vector<std::shared_ptr<Bombers>>& bombers,
	std::vector<std::shared_ptr<BomberSprite>>& bomber_sprites)
{
	if (initialization)
	{
		initialLanders(player, lander_objects, lander_sprites);
		initialization = false; //Done initializing
		lander_watch->restart();
		return;
	}
	auto _time = world_watch->time_elapsed();
	createLander(lander_objects, lander_sprites, player);

	if (_time < 1.5f || enemy == Enemy::None)
		return;

	switch (enemy)
	{
	case Enemy::Lander:
		createLander(lander_objects, lander_sprites, player);
		break;
	case Enemy::Bomber:
		createBomber(bombers, bomber_sprites, player);
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
	garbageCollector(missile_sprites);
}

void GameWorld::initialLanders(std::shared_ptr<Player>& player, std::vector<std::shared_ptr<Lander>>& lander_objects, std::vector<std::shared_ptr<LanderSprite>>& lander_sprites)
{
	//create initial wave of landers when game starts
	for (int i = 0; i < 4; i++)
	{
		auto lander_object = std::make_shared<Lander>(player, initialization);
		lander_objects.push_back(lander_object);

		auto lander_sprite = std::make_shared<LanderSprite>();
		lander_sprites.push_back(lander_sprite);
	}
	world_watch->restart();
}

Enemy GameWorld::generateEnemy()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	int min = 0;
	int max = 2;
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
	std::vector<std::shared_ptr<LanderSprite>>& lander_sprites, std::shared_ptr<Player>& player)
{
	if (lander_watch->time_elapsed() >= 5.0f) //landers are at least spawned at 5 sec intervals
	{
		auto landerCountWithinScreen = 0;
		auto [playerXpos, playerYpos] = player->getPlayerPosition();
		for (auto lander : lander_objects)
		{
			auto [landerXpos, landerYpos] = lander->getPosition();
			auto distance = fabs(playerXpos - landerXpos); //get the absolute distance between player and lander
			if (distance < 400.0f) //This distance is likely to change once game is pragrammed to function in full screen mode
			{
				//This lander is within the screen
				++landerCountWithinScreen; //increment number of landers within screen
			}
		}
		if (landerCountWithinScreen <= 1) //spawn lander if there is zero or 1 lander within screen
		{
			//Generate 1 or 2 more landers within screen
			std::random_device rd;
			std::mt19937 gen(rd());
			int min = 1;
			int max = 2;
			std::uniform_int_distribution<int>distribution(min, max);
			auto numberOfLandersToSpawn = distribution(gen); //randomly generate the number of landers to spawn

			auto landerYpos = 150.0f;//Landers will spawn at this height
			for (int i = 0; i < numberOfLandersToSpawn; ++i)
			{
				//Create lander objects.
				//Need to decide if it should be on the left or right hand side of screen.
				if (i == 0)
				{
					//Generate lander on the left
					auto landerXpos = playerXpos - 320.0f; //The 320 will change for full screen
					auto lander_object = std::make_shared<Lander>(player, initialization);
					lander_object->setPosition(landerXpos, landerYpos);
					auto isRight = false;
					auto isLeft = true;
					lander_object->setSide(isRight, isLeft);
					lander_objects.push_back(lander_object);

					//corresponding sprite object
					auto lander_sprite = std::make_shared<LanderSprite>();
					lander_sprites.push_back(lander_sprite);
					continue; //Should not generate lander on the right side if this conditional evaluated to true
				}
			
				//Generate lander on the right
				auto landerXpos = playerXpos + 320.0f;
				auto lander_object = std::make_shared<Lander>(player, initialization);
				lander_object->setPosition(landerXpos, landerYpos);
				auto isRight = true;
				auto isLeft = false;
				lander_object->setSide(isRight, isLeft);
				lander_objects.push_back(lander_object);

				//corresponding sprite object
				auto lander_sprite = std::make_shared<LanderSprite>();
				lander_sprites.push_back(lander_sprite);
			}
		}
		lander_watch->restart();
	}
}

void GameWorld::placeHumanoids(std::vector<std::shared_ptr<Humanoid>>& humanoid_objects,
	std::vector<std::shared_ptr<HumanoidSprite>>& humanoid_sprites)
{
	//generate 5 humanoids
	for (int i = 0; i < 5; ++i)
	{
		auto humanoid = std::make_shared<Humanoid>();
		humanoid_objects.push_back(humanoid);
		auto humanoid_sprite = std::make_shared<HumanoidSprite>();
		humanoid_sprites.push_back(humanoid_sprite);
	}
}

void GameWorld::garbageCollector(std::vector<std::shared_ptr<MissileSprite>>& missile_sprites)
{
	auto _projectiles = shooter_obj->getProjectiles();
	auto missile_sprite = missile_sprites.begin();
	auto projectile_iter = _projectiles.begin();

	while (projectile_iter != _projectiles.end())
	{
		

		if ((*projectile_iter)->getDelete())
		{
			shooter_obj->deleteProjectile((*projectile_iter)->getProjectileId());
			_projectiles.erase(projectile_iter);
			missile_sprites.erase(missile_sprite);
		}

		else
		{
			++projectile_iter;
			++missile_sprite;
		}
	}
}

void GameWorld::createBomber(std::vector<std::shared_ptr<Bombers>>& bombers,
	std::vector<std::shared_ptr<BomberSprite>>& bomber_sprites, std::shared_ptr<Player>& player)
{
	auto bomber = std::make_shared<Bombers>(player);
	bombers.push_back(bomber);

	auto bomber_sprite = std::make_shared<BomberSprite>();
	bomber_sprites.push_back(bomber_sprite);
}

#include "game.h"

void Game::updateGame(const float dt)
{
	if (!isPlaying)
		return;

	player_obj->updatePlayer(leftPressed, rightPressed, upPressed, downPressed, spacePressed, player_sprite,
		laser_sprite, lasers, dt, gameOver);

	if (player_obj->getPlayerState() == PlayerState::Dead)
		return;

	updateHumanoids(dt);

	game_world->updateGameWorld(lander_objects, lander_object_sprites, player_obj, lander_missile_sprites,bombers, bomber_sprites);

	if (!lander_objects.empty())
		updateLanders(dt);

	updateProjectiles(dt);
	updateCollisions();
	updateGameState();
	updateBombers(dt);
	updateScore();
}

void Game::updateLanders(const float dt)
{
	auto object_iter = lander_objects.begin();
	auto sprite_iter = lander_object_sprites.begin();
	while (object_iter != lander_objects.end())
	{
		(*object_iter)->updateLander(*sprite_iter,dt,player_obj,lander_missile_sprites,humanoid_objects);

		if ((*object_iter)->canRemove())
		{
			lander_objects.erase(object_iter);
			lander_object_sprites.erase(sprite_iter);
		}
		else
		{
			++object_iter;
			++sprite_iter;
		}
	}
}

void Game::updateCollisions()
{
	//update_collisions.playerLanderCollisions(player_obj, lander_objects, lander_object_sprites);
	update_collisions.landerAndLaserCollisions(lander_objects, laser_sprite, lasers, humanoid_objects,player_obj, manage_score, landersDestroyed);

	update_collisions.landerAndHumanoidCollisions(lander_objects,lander_object_sprites, humanoid_objects,humanoid_sprites, number0fHumanoids);
	update_collisions.playerAndFallingHumanoidCollisions(player_obj, humanoid_objects,humanoid_sprites, manage_score);
	update_collisions.humanoidAndGroundCollisions(humanoid_objects,humanoid_sprites, number0fHumanoids);
	update_collisions.playerLaserAndHumanoidCollisions(humanoid_objects, humanoid_sprites, laser_sprite, lasers, number0fHumanoids);
	//update_collisions.playerAndMissileCollisions(player_obj, lander_missile_sprites);
	update_collisions.LaserAndBomberCollisions(bombers, bomber_sprites, lasers, laser_sprite, player_obj, manage_score);
	//update_collisions.MineAndPlayerCollisions(mines, mine_sprites, player_obj);
	//update_collisions.playerAndBomberCollisions(bombers, bomber_sprites, player_obj);
}

void Game::updateHumanoids(const float dt)
{
	auto humanoid_sprite = humanoid_sprites.begin();
	auto humanoid = humanoid_objects.begin();
	while (humanoid != humanoid_objects.end())
	{
		(*humanoid)->updateHumanoid(dt, *humanoid_sprite,player_obj);
		++humanoid;
		++humanoid_sprite;
	}
}

void Game::updateProjectiles(const float dt)
{
	std::shared_ptr<Lander>lander_object = std::make_shared<Lander>();
	lander_object->updateMissileSprites(lander_missile_sprites);
	shooter_object->updateProjectile(dt,ProjectileType::LanderMissile, lander_missile_sprites);
}

void Game::updateGameState()
{
	auto totalLanders = 6;
	if (landersDestroyed == totalLanders)
	{
		playerWon = true;
		return;
	}

	/*if (number0fHumanoids == 0)
	{
		gameOver = true;
	}*/
}

void Game::updateBombers(const float dt)
{
	auto bomber = bombers.begin();
	auto bomber_sprite = bomber_sprites.begin();

	while (bomber != bombers.end())
	{
		(*bomber)->update(player_obj, *bomber_sprite,mines, mine_sprites, dt);
		++bomber;
		++bomber_sprite;
	}

	if (bombers.empty())
	{
		auto mine_obj = std::make_shared<Mine>();
		mine_obj->updateMine(mines, mine_sprites);
	}
}

void Game::updateScore()
{
	auto [xPlayerPos, yPlayerPos] = player_obj->getPlayerPosition();
	std::string _highScore = std::to_string(manage_score->getHighScore());
	highScorePosition.x = xPlayerPos + 300.0f;
	highScore.setString("High Score: " + _highScore);
	highScore.setPosition(highScorePosition);

	std::string _currentScore = std::to_string(player_obj->getScore());
	currentScore.setString("Score: " + _currentScore);
	currentScorePosition.x = xPlayerPos - 400.0f;
	currentScore.setPosition(currentScorePosition);
}
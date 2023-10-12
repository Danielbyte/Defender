#include "../game-source-code/game.h"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

//stop watch test cases
TEST_CASE("Test if stop watch can function as a timer")
{
	std::shared_ptr<StopWatch>stop_watch = std::make_shared<StopWatch>();

	auto initial_time = stop_watch->time_elapsed();
	
	//Pass some time
	while (stop_watch->time_elapsed() < 0.1f)
	{
		//do nothing
	}

	//get the time after passing some
	auto final_time = stop_watch->time_elapsed();
	
	//final time should be greater than initial time
	DOCTEST_CHECK_GT(final_time, initial_time);

	//initial time should be lesser than final time
	DOCTEST_CHECK_LE(initial_time, final_time);
}

TEST_CASE("Test if timer can be stopped")
{
	std::shared_ptr<StopWatch>stop_watch = std::make_shared<StopWatch>();
	auto initial_time = stop_watch->time_elapsed();
	//Pass some time
	while (stop_watch->time_elapsed() < 0.1f)
	{
		//do nothing
	}
	//stop the watch
	stop_watch->stop();

	auto final_time1 = stop_watch->time_elapsed();
	auto final_time2 = stop_watch->time_elapsed();

	//final_time1 and final_time2 should be equal
	DOCTEST_CHECK_EQ(final_time1, final_time2);
	//final_time1 and final_time2 should be greater than initial time
	DOCTEST_CHECK_GT(final_time1, initial_time);
	DOCTEST_CHECK_GT(final_time2, initial_time);
}

TEST_CASE("Test if timer can be restarted")
{
	std::shared_ptr<StopWatch>stop_watch = std::make_shared<StopWatch>();
	//Pass some time
	while (stop_watch->time_elapsed() < 0.1f)
	{
		//do nothing
	}
	//record the time
	auto initial_time = stop_watch->time_elapsed();

	//restart stop watch
	stop_watch->restart();
	auto final_time = stop_watch->time_elapsed();

	//final time should be lesser than initial time
	DOCTEST_CHECK_LE(final_time, initial_time);
	DOCTEST_CHECK_GT(initial_time, final_time);
}

//Test cases for the player object
auto playerSpawnPosition_x = 400.0f;
auto playerSpawnPosition_y = 300.0f;
auto initialPlayerDirection = "right";
auto deltaTime = 10.0f;
auto playerSpeed = 250.0f;
auto lowerrBound = 590.0f;
auto upperBound = 110.0f;

TEST_CASE("Test if player is spawned at the right position")
{
	auto player = std::make_shared<Player>();
	auto [xPosition, yPosition] = player->getPlayerPosition();

	CHECK_EQ(xPosition, playerSpawnPosition_x);
	CHECK_EQ(yPosition, playerSpawnPosition_y);
}

TEST_CASE("Check if the initial player state is alive")
{
	auto player = std::make_shared<Player>();
	PlayerState state = player->getPlayerState();
	CHECK_EQ(state, PlayerState::Alive);
}

TEST_CASE("Test if player state can be correctly set")
{
	auto player = std::make_shared<Player>();
	auto initial_state = player->getPlayerState();
	player->setPlayerState(PlayerState::Dead);
	auto final_state = player->getPlayerState();

	//initially, the player should be alive
	CHECK_EQ(initial_state, PlayerState::Alive);
	//After the player state has been set to dead, player state should be dead
	CHECK_EQ(final_state, PlayerState::Dead);
}

TEST_CASE("Test if the initial player direction is to the right")
{
	auto player = std::make_shared<Player>();
	auto direction = player->getDirection();
	CHECK_EQ(direction, initialPlayerDirection);
}

TEST_CASE("Test if player direction is updated to face left if user presses left or right arrow keys")
{
	auto player = std::make_shared<Player>();
	auto player_sprite = std::make_shared<PlayerSprite>();
	std::vector<std::shared_ptr<LaserSprite>>laser_sprites;
	std::vector<std::shared_ptr<Projectile>>lasers;

	auto initial_direction = player->getDirection();
	auto left = true;
	auto right = false;
	auto up = false;
	auto down = false;
	auto space = false;
	auto gameOver = false;
	player->updatePlayer(left, right, up, down, space, player_sprite, laser_sprites,lasers ,deltaTime, gameOver);

	auto final_direction = player->getDirection();

	//initial player direction should be to the right
	CHECK_EQ(initial_direction, initialPlayerDirection);
	//after user presses left arrow key, player direction should be to the left
	CHECK_EQ(final_direction, "left");

	//now user presses right
	right = true;
	left = false;
	player->updatePlayer(left, right, up, down, space, player_sprite, laser_sprites,lasers, deltaTime, gameOver);
	final_direction = player->getDirection();

	//The player should now face the right
	CHECK_EQ(final_direction, "right");
}

TEST_CASE("Test if player position is updated when user presses right arrow key")
{
	auto player = std::make_shared<Player>();
	auto player_sprite = std::make_shared<PlayerSprite>();
	std::vector<std::shared_ptr<LaserSprite>>laser_sprites;
	std::vector<std::shared_ptr<Projectile>>lasers;

	auto initial_direction = player->getDirection();
	auto left = false;
	auto right = true;
	auto up = false;
	auto down = false;
	auto space = false;
	auto gameOver = false;
	auto [initialXpos, initialYpos] = player->getPlayerPosition();
	player->updatePlayer(left, right, up, down, space, player_sprite, laser_sprites,lasers, deltaTime, gameOver);
	auto [finalXpos, finalYpos] = player->getPlayerPosition();

	//Expect initial positions before player presses right arrow
	CHECK(initialXpos == playerSpawnPosition_x);
	CHECK(initialYpos == playerSpawnPosition_y);

	//Expected positions after player moves right
	auto expectedXposition = playerSpawnPosition_x + playerSpeed * deltaTime;
	auto expectedYpos = playerSpawnPosition_y;
	CHECK_EQ(finalXpos, expectedXposition);
	CHECK_EQ(finalYpos, expectedYpos);
}

TEST_CASE("Test if player position is updated when user presses left arrow key")
{
	auto player = std::make_shared<Player>();
	auto player_sprite = std::make_shared<PlayerSprite>();
	std::vector<std::shared_ptr<LaserSprite>>laser_sprites;
	std::vector<std::shared_ptr<Projectile>>lasers;

	auto initial_direction = player->getDirection();
	auto left = true;
	auto right = false;
	auto up = false;
	auto down = false;
	auto space = false;
	auto gameOver = false;
	auto [initialXpos, initialYpos] = player->getPlayerPosition();
	player->updatePlayer(left, right, up, down, space, player_sprite, laser_sprites,lasers, deltaTime, gameOver);
	auto [finalXpos, finalYpos] = player->getPlayerPosition();

	//Expect initial positions before player presses right arrow
	CHECK(initialXpos == playerSpawnPosition_x);
	CHECK(initialYpos == playerSpawnPosition_y);

	//Expected positions after player moves left
	auto expectedXposition = playerSpawnPosition_x - playerSpeed * deltaTime;
	auto expectedYpos = playerSpawnPosition_y;
	CHECK_EQ(finalXpos, expectedXposition);
	CHECK_EQ(finalYpos, expectedYpos);
}

TEST_CASE("Test if player position is updated when user presses down key")
{
	auto player = std::make_shared<Player>();
	auto player_sprite = std::make_shared<PlayerSprite>();
	std::vector<std::shared_ptr<LaserSprite>>laser_sprites;
	std::vector<std::shared_ptr<Projectile>>lasers;

	auto left = false;
	auto right = false;
	auto up = false;
	auto down = true;
	auto space = false;
	auto gameOver = false;
	deltaTime = 0.2f;
	auto [initialXpos, initialYpos] = player->getPlayerPosition();
	player->updatePlayer(left, right, up, down, space, player_sprite, laser_sprites,lasers, deltaTime, gameOver);
	auto [finalXpos, finalYpos] = player->getPlayerPosition();

	//Expect initial positions before player presses down arrow
	CHECK(initialXpos == playerSpawnPosition_x);
	CHECK(initialYpos == playerSpawnPosition_y);

	//Expected positions after player moves down
	auto expectedYposition = playerSpawnPosition_y + playerSpeed * deltaTime;
	auto expectedXpos = playerSpawnPosition_x;
	CHECK_EQ(finalYpos, expectedYposition);
	CHECK_EQ(finalXpos, expectedXpos);
}

TEST_CASE("Test if user is correctly updated when user presses up key")
{
	auto player = std::make_shared<Player>();
	auto player_sprite = std::make_shared<PlayerSprite>();
	std::vector<std::shared_ptr<LaserSprite>>laser_sprites;
	std::vector<std::shared_ptr<Projectile>>lasers;

	auto left = false;
	auto right = false;
	auto up = true;
	auto down = false;
	auto space = false;
	auto gameOver = false;
	deltaTime = 0.2f;
	auto [initialXpos, initialYpos] = player->getPlayerPosition();
	player->updatePlayer(left, right, up, down, space, player_sprite, laser_sprites, lasers, deltaTime, gameOver);
	auto [finalXpos, finalYpos] = player->getPlayerPosition();

	//Expect initial positions before player presses up arrow
	CHECK(initialXpos == playerSpawnPosition_x);
	CHECK(initialYpos == playerSpawnPosition_y);

	//Expected positions after player moves up
	auto expectedYposition = playerSpawnPosition_y - playerSpeed * deltaTime;
	auto expectedXpos = playerSpawnPosition_x;
	CHECK_EQ(finalYpos, expectedYposition);
	CHECK_EQ(finalXpos, expectedXpos);

	//reset delta time
	deltaTime = 10.0f;
}

TEST_CASE("Test if player is restricted to the upper bound of the screen")
{
	auto player = std::make_shared<Player>();
	auto player_sprite = std::make_shared<PlayerSprite>();
	std::vector<std::shared_ptr<LaserSprite>>laser_sprites;
	std::vector<std::shared_ptr<Projectile>>lasers;

	auto left = false;
	auto right = false;
	auto up = true; //will move 2500 units up
	auto down = false;
	auto space = false;
	auto gameOver = false;
	player->updatePlayer(left, right, up, down, space, player_sprite, laser_sprites, lasers, deltaTime, gameOver);
	auto [finalXpos, finalYpos] = player->getPlayerPosition();

	//Expected positions after player moves up (out of bounds)
	auto expectedYposition = upperBound;
	auto expectedXpos = playerSpawnPosition_x;
	CHECK_EQ(finalYpos, expectedYposition);
	CHECK_EQ(finalXpos, expectedXpos);
}

TEST_CASE("Test if player is restricted to lower bounds of game screen")
{
	auto player = std::make_shared<Player>();
	auto player_sprite = std::make_shared<PlayerSprite>();
	std::vector<std::shared_ptr<LaserSprite>>laser_sprites;
	std::vector<std::shared_ptr<Projectile>>lasers;

	auto left = false;
	auto right = false;
	auto up = false; 
	auto down = true;//will move 2500 units down
	auto space = false;
	auto gameOver = false;
	player->updatePlayer(left, right, up, down, space, player_sprite, laser_sprites, lasers, deltaTime, gameOver);
	auto [finalXpos, finalYpos] = player->getPlayerPosition();

	//Expected positions after player moves down (out of bounds)
	auto expectedYposition = lowerrBound;
	auto expectedXpos = playerSpawnPosition_x;
	CHECK_EQ(finalYpos, expectedYposition);
	CHECK_EQ(finalXpos, expectedXpos);
}

TEST_CASE("Test if player flies towards and beyond the right edge of the game screen")
{
	auto player = std::make_shared<Player>();
	auto player_sprite = std::make_shared<PlayerSprite>();
	std::vector<std::shared_ptr<LaserSprite>>laser_sprites;
	std::vector<std::shared_ptr<Projectile>>lasers;

	auto left = false;
	auto right = true; //will move 2500 units right
	auto up = false;
	auto down = false;
	auto space = false;
	auto gameOver = false;
	player->updatePlayer(left, right, up, down, space, player_sprite, laser_sprites, lasers, deltaTime, gameOver);
	auto [finalXpos, finalYpos] = player->getPlayerPosition();

	//Expected positions after player moves 2500 units right;
	auto expectedYposition = playerSpawnPosition_y;
	auto expectedXpos = playerSpawnPosition_x + playerSpeed * deltaTime;

	CHECK(finalXpos == expectedXpos);
	CHECK(finalYpos == expectedYposition);
}

TEST_CASE("Test if player flies towards and beyond the left edge of the game screen")
{
	auto player = std::make_shared<Player>();
	auto player_sprite = std::make_shared<PlayerSprite>();
	std::vector<std::shared_ptr<LaserSprite>>laser_sprites;
	std::vector<std::shared_ptr<Projectile>>lasers;

	auto left = true; //will move 2500 units right
	auto right = false; 
	auto up = false;
	auto down = false;
	auto space = false;
	auto gameOver = false;
	player->updatePlayer(left, right, up, down, space, player_sprite, laser_sprites, lasers, deltaTime, gameOver);
	auto [finalXpos, finalYpos] = player->getPlayerPosition();

	//Expected positions after player moves 2500 units left;
	auto expectedYposition = playerSpawnPosition_y;
	auto expectedXpos = playerSpawnPosition_x - playerSpeed * deltaTime;

	CHECK(finalXpos == expectedXpos);
	CHECK(finalYpos == expectedYposition);
}

TEST_CASE("Test if a laser is generated if user presses space key")
{
	auto player = std::make_shared<Player>();
	auto player_sprite = std::make_shared<PlayerSprite>();
	std::vector<std::shared_ptr<LaserSprite>>laser_sprites;
	std::vector<std::shared_ptr<Projectile>>lasers;

	auto left = false;
	auto right = false;
	auto up = false;
	auto down = false;
	auto space = true;;
	auto gameOver = false;

	//no laser sprites prior space press
	CHECK(laser_sprites.empty() == true);
	player->updatePlayer(left, right, up, down, space, player_sprite, laser_sprites, lasers, deltaTime, gameOver);
	//laser should have lasers sprites afte space key press
	CHECK(laser_sprites.empty() == false);
}

//Test cases for the humanoid object
auto humanoidSpeed = 0.9f;
auto abductionSpeed = 50.0f; //vertical humanoid speed changes on abduction to make sure it sync with lander speed 

TEST_CASE("Test if the humanoid is in an initial moving state")
{
	auto humanoid = std::make_shared<Humanoid>();
	auto state = humanoid->getHumanoidState();
	CHECK_EQ(state, HumanoidState::Walking);
}

TEST_CASE("Test if humanoid state can be correctly set")
{
	auto humanoid = std::make_shared<Humanoid>();
	HumanoidState initial_state = humanoid->getHumanoidState();
	humanoid->setHumanoidState(HumanoidState::Abducted);
	HumanoidState final_state = humanoid->getHumanoidState();

	CHECK(initial_state == HumanoidState::Walking);
	CHECK(final_state == HumanoidState::Abducted);
}

TEST_CASE("Test if humanoid is given direction")
{
	auto humanoid = std::make_shared<Humanoid>();
	auto direction = humanoid->getHumanoidDirection();
	int counter = 0;
	
	//The direction is randomly generated
	if (direction == "right")
	{
		CHECK(direction == "right");
		++counter;
	}

	if (direction == "left")
	{
		CHECK(direction == "left");
		++counter;
	}

	//counter should be exactly 1
	CHECK(counter == 1);
}

TEST_CASE("Test if humanoid moves to the right or left depending on spawning position")
{
	auto humanoid = std::make_shared<Humanoid>();
	auto player = std::make_shared<Player>();
	auto humanoid_sprite = std::make_shared<HumanoidSprite>();
	auto direction = humanoid->getHumanoidDirection();
	auto [initXPosition, initYPosition] = humanoid->getPosition();

	humanoid->updateHumanoid(deltaTime, humanoid_sprite, player);
	//capture humanoid position after update
	auto [finalXposition, finalYposition] = humanoid->getPosition();

	if (direction == "right")
	{
		//humanoid should be moving towards the right
		auto expectedXpos = initXPosition + humanoidSpeed * deltaTime;
		auto expectedYpos = initYPosition;
		CHECK(finalXposition == expectedXpos);
		CHECK(finalYposition == expectedYpos);
	}

	if (direction == "left")
	{
		//humanoid should be moving towards the left
		auto expectedXpos = initXPosition - humanoidSpeed * deltaTime;
		auto expectedYpos = initYPosition;
		CHECK(finalXposition == expectedXpos);
		CHECK(finalYposition == expectedYpos);
	}
}

TEST_CASE("Test if humanoid can move up once abducted")
{
	auto humanoid = std::make_shared<Humanoid>();
	auto humanoid_sprite = std::make_shared<HumanoidSprite>();
	auto player = std::make_shared<Player>();
	auto [initXpos, initYpos] = humanoid->getPosition();

	humanoid->setToAbducted();

	//update humanoid
	humanoid->updateHumanoid(deltaTime, humanoid_sprite, player);
	//Capture humanoid position after abduction
	auto [finalXpos, finalYpos] = humanoid->getPosition();

	auto expectedYpos = initYpos - abductionSpeed * deltaTime;
	auto expectedXpos = initXpos; //no movement int the vertical 
	CHECK(finalYpos == expectedYpos);
	CHECK(finalXpos == expectedXpos);
}

TEST_CASE("Test if humanoid falls to its death after abducting lander is shot by player")
{
	auto humanoid = std::make_shared<Humanoid>();
	auto humanoid_sprite = std::make_shared<HumanoidSprite>();
	auto player = std::make_shared<Player>();
	auto [initXpos, initYpos] = humanoid->getPosition();

	//model abduction of humanoid
	humanoid->setToAbducted();
	humanoid->updateHumanoid(deltaTime, humanoid_sprite, player);
	humanoid->updateHumanoid(deltaTime, humanoid_sprite, player);
	auto [secondXpos, secondYpos] = humanoid->getPosition();
	//Model abducting lander getting shot
	humanoid->setHumanoidState(HumanoidState::Falling);
	//update humanoid
	humanoid->updateHumanoid(deltaTime,humanoid_sprite,player);
	auto [thirdXpos, thirdYpos] = humanoid->getPosition();

	auto expectedYpos = secondYpos + abductionSpeed * deltaTime;
	CHECK(thirdYpos == expectedYpos);

	//initial position should be greater than second position
	CHECK_GT(initYpos, secondYpos);
	//third position should be greater than second position
	CHECK_GT(thirdYpos, secondYpos);

	//horizontal position of humanoid should remain unchanged
	CHECK_EQ(initXpos, secondXpos);
	CHECK_EQ(secondXpos, thirdXpos);
}

//Test cases for the lander object
auto landerSpeed = 50.0f;
auto landerHumanoidZone = 480.0f;

TEST_CASE("Test if lander is generated in either left or right side of player")
{
	auto player = std::make_shared<Player>();
	auto lander = std::make_shared<Lander>(player);
	auto counter = 0;

	auto [right, left] = lander->test_getSide();

	if (right)
	{
		CHECK(right == true);
		++counter;
	}

	if (left)
	{
		CHECK(left == true);
		++counter;
	}

	//counter should be exactly 1
	CHECK(counter == 1);
}

TEST_CASE("Test if lander side is set with respect to player position")
{
	auto player = std::make_shared<Player>();
	auto lander = std::make_shared<Lander>(player);
	auto counter = 0;

	auto [right, left] = lander->test_getSide();
	auto [landerXpos, landerYpos] = lander->getPosition();
	auto [playerXpos, playerYpos] = player->getPlayerPosition();

	if (right)
	{
		CHECK_GT(landerXpos, playerXpos);
	}

	if (left)
	{
		CHECK_LE(landerXpos, playerXpos);
	}
}

TEST_CASE("Test if lander can detect once it reaches the humanoid region")
{
	auto player = std::make_shared<Player>();
	auto lander = std::make_shared<Lander>(player);

	auto lander_sprite = std::make_shared<LanderSprite>();
	std::vector<std::shared_ptr<MissileSprite>> missile_sprites;
	std::vector<std::shared_ptr<Humanoid>> humanoids;


	auto inHumanoidZone = lander->test_getIfInHumanoidZone();
	//lander should initially be not in humanoid zone
	CHECK(inHumanoidZone == false);
	lander->updateLander(lander_sprite, deltaTime, player, missile_sprites, humanoids);

	//keep moving lander until it reaches the humanoid zone
	for (int i = 0; i <= 100; ++i)
		lander->moveSouth(deltaTime);

	lander->test_setTeleportationState(false);

	lander->updateLander(lander_sprite, deltaTime, player, missile_sprites, humanoids);
	inHumanoidZone = lander->test_getIfInHumanoidZone();
	CHECK(inHumanoidZone == true);
}

TEST_CASE("Test if lander can move straight East")
{
	auto lander = std::make_shared<Lander>();
	auto [initXpos, initYpos] = lander->getPosition();
	lander->moveEast(deltaTime);
	//Get the lander position after moving eas
	auto [finalXpos, finalYpos] = lander->getPosition();
	auto expectedXpos = initXpos + landerSpeed * deltaTime;
	auto expectedYpos = initYpos;

	CHECK(finalXpos == expectedXpos);
	CHECK(finalYpos == expectedYpos);
}

TEST_CASE("Test if lander can move West")
{
	auto lander = std::make_shared<Lander>();
	auto [initXpos, initYpos] = lander->getPosition();
	lander->moveWest(deltaTime);

	auto [finalXpos, finalYpos] = lander->getPosition();
	auto expectedXpos = initXpos - landerSpeed * deltaTime;
	auto expectedYpos = initYpos;

	CHECK(finalXpos == expectedXpos);
	CHECK(finalYpos == expectedYpos);
}

TEST_CASE("Test if lander can move South")
{
	auto lander = std::make_shared<Lander>();
	auto [initXpos, initYpos] = lander->getPosition();

	auto dt = 0.02f;
	lander->moveSouth(dt);
	auto [finalXpos, finalYpos] = lander->getPosition();
	auto expectedYpos = initYpos + landerSpeed * dt;
	auto expectedXpos = initXpos;
	CHECK_EQ(finalXpos, expectedXpos);
	CHECK_EQ(finalYpos, expectedYpos);
}

TEST_CASE("Test if lander moves North")
{
	auto lander = std::make_shared<Lander>();
	auto [initXpos, initYpos] = lander->getPosition();
	lander->moveNorth(deltaTime);
	auto [finalXpos, finalYpos] = lander->getPosition();
	auto expectedXpos = initXpos;
	auto expectedYpos = initYpos - landerSpeed * deltaTime;
	CHECK_EQ(finalXpos, expectedXpos);
	CHECK_EQ(finalYpos, expectedYpos);
}

TEST_CASE("Test if lander moves North Easterly")
{
	auto lander = std::make_shared<Lander>();
	auto [initXpos, initYpos] = lander->getPosition();
	auto dt = 0.02f;
	lander->moveNorthEast(dt);
	auto [finalXpos, finalYpos] = lander->getPosition();
	auto expectedYpos = initYpos - landerSpeed * dt;
	auto expectedXpos = initXpos + landerSpeed * dt;
	CHECK_EQ(finalXpos, expectedXpos);
	CHECK_EQ(finalYpos, expectedYpos);

}

TEST_CASE("Test if lander moves South Easterly")
{
	auto lander = std::make_shared<Lander>();
	auto [initXpos, initYpos] = lander->getPosition();
	auto dt = 0.02f;
	lander->moveSouthEast(dt);
	auto [finalXpos, finalYpos] = lander->getPosition();
	auto expectedXpos = initXpos + landerSpeed * dt;
	auto expectedYpos = initYpos + landerSpeed * dt;
	CHECK_EQ(finalXpos, expectedXpos);
	CHECK_EQ(finalYpos, expectedYpos);
}

TEST_CASE("Test if lander moves South Westerly")
{
	auto lander = std::make_shared<Lander>();
	auto [initXpos, initYpos] = lander->getPosition();
	auto dt = 0.02f;
	lander->moveSouthWest(dt);
	auto [finalXpos, finalYpos] = lander->getPosition();
	auto expectedXpos = initXpos - landerSpeed * dt;
	auto expectesYpos = initYpos + landerSpeed * dt;
	CHECK_EQ(finalXpos, expectedXpos);
	CHECK_EQ(finalYpos, expectesYpos);
}

TEST_CASE("Test if lander can move North Westerly")
{
	auto lander = std::make_shared<Lander>();
	auto [initXpos, initYpos] = lander->getPosition();
	auto dt = 0.02f;
	lander->moveNorthWest(dt);
	auto [finalXpos, finalYpos] = lander->getPosition();
	auto expectedXpos = initXpos - landerSpeed * dt;
	auto expectedYpos = initYpos - landerSpeed * dt;
	CHECK_EQ(finalXpos, expectedXpos);
	CHECK_EQ(finalYpos, expectedYpos);
}

//Bomber test cases
auto bomberPositionOffset = 500.0f;
auto bomberSpeed = 50.0f;
auto dt = 1.0f / 60.0f;
TEST_CASE("Test if bomber is spawned at the right of player if player is facing right")
{
	auto player = std::make_shared<Player>();
	auto bomber = std::make_shared<Bombers>(player);
	auto [xPlayerPos, yPlayerPos] = player->getPlayerPosition();
	auto [xBomberPos, yBomberPos] = bomber->getPosition();
	CHECK_GT(xBomberPos, xPlayerPos);
	CHECK_EQ(yBomberPos, yPlayerPos);
}

TEST_CASE("Test if bomber is spawned at the left side of player if player is facing left")
{
	auto player = std::make_shared<Player>();
	auto player_sprite = std::make_shared<PlayerSprite>();
	std::vector<std::shared_ptr<LaserSprite>>laser_sprites;
	std::vector<std::shared_ptr<Projectile>>lasers;

	//Update player to face left
	auto left = true;
	auto right = false;
	auto up = false;
	auto down = false;
	auto space = false;
	auto gameOver = false;
	player->updatePlayer(left, right, up, down, space, player_sprite, laser_sprites, lasers, deltaTime, gameOver);
	
	auto bomber = std::make_shared<Bombers>(player);
	auto [xPlayerPos, yPlayerPos] = player->getPlayerPosition();
	auto [xBomberPos, yBomberPos] = bomber->getPosition();
	CHECK_LE(xBomberPos, xPlayerPos);
	CHECK_EQ(yBomberPos, yPlayerPos);
}

TEST_CASE("Test if bomber position can be correctly retrieved if player faces right")
{
	auto player = std::make_shared<Player>();
	auto bomber = std::make_shared<Bombers>(player);
	auto [xPlayerPos, yPlayerPos] = player->getPlayerPosition();
	auto [xBomberPos, yBomberPos] = bomber->getPosition();

	//Player facing right
	auto expectedBomberXposition = xPlayerPos + bomberPositionOffset;
	auto expectedBomberYposition = yPlayerPos;
	CHECK_EQ(xBomberPos, expectedBomberXposition);
	CHECK_EQ(yBomberPos, expectedBomberYposition);
}

TEST_CASE("Test if bomber position can be correctly retrieved if player faces left")
{
	auto player = std::make_shared<Player>();
	auto player_sprite = std::make_shared<PlayerSprite>();
	std::vector<std::shared_ptr<LaserSprite>>laser_sprites;
	std::vector<std::shared_ptr<Projectile>>lasers;

	//Update player to face left
	auto left = true;
	auto right = false;
	auto up = false;
	auto down = false;
	auto space = false;
	auto gameOver = false;
	player->updatePlayer(left, right, up, down, space, player_sprite, laser_sprites, lasers, deltaTime, gameOver);

	auto bomber = std::make_shared<Bombers>(player);
	auto [xPlayerPos, yPlayerPos] = player->getPlayerPosition();
	auto [xBomberPos, yBomberPos] = bomber->getPosition();

	//Player facing right
	auto expectedBomberXposition = xPlayerPos - bomberPositionOffset;
	auto expectedBomberYposition = yPlayerPos;
	CHECK_EQ(xBomberPos, expectedBomberXposition);
	CHECK_EQ(yBomberPos, expectedBomberYposition);
}

TEST_CASE("Test if bomber can move South")
{
	auto player = std::make_shared<Player>();
	auto bomber = std::make_shared<Bombers>(player);
	auto [xPlayerPos, yPlayerPos] = player->getPlayerPosition();
	auto [xBomberPos, yBomberPos] = bomber->getPosition();

	bomber->moveSouth(dt);

	auto [finalBomberXpos, finalBomberYpos] = bomber->getPosition();
	auto expectedYpos = yBomberPos + bomberSpeed * dt;
	auto expectedXpos = xBomberPos;
	CHECK_EQ(finalBomberXpos, expectedXpos);
	CHECK_EQ(finalBomberYpos, expectedYpos);
}

TEST_CASE("Test if bomber can move North")
{
	auto player = std::make_shared<Player>();
	auto bomber = std::make_shared<Bombers>(player);
	auto [xPlayerPos, yPlayerPos] = player->getPlayerPosition();
	auto [xBomberPos, yBomberPos] = bomber->getPosition();

	bomber->moveNorth(dt);

	auto [finalBomberXpos, finalBomberYpos] = bomber->getPosition();
	auto expectedYpos = yBomberPos - bomberSpeed * dt;
	auto expectedXpos = xBomberPos;
	CHECK_EQ(finalBomberXpos, expectedXpos);
	CHECK_EQ(finalBomberYpos, expectedYpos);
}

TEST_CASE("Test if bomber can travel North Easterly")
{
	auto player = std::make_shared<Player>();
	auto bomber = std::make_shared<Bombers>(player);
	auto [xPlayerPos, yPlayerPos] = player->getPlayerPosition();
	auto [xBomberPos, yBomberPos] = bomber->getPosition();

	bomber->moveNorthEast(dt);

	auto [finalBomberXpos, finalBomberYpos] = bomber->getPosition();
	auto expectedYpos = yBomberPos - bomberSpeed * dt;
	auto expectedXpos = xBomberPos + bomberSpeed * dt;

	CHECK_EQ(finalBomberXpos, expectedXpos);
	CHECK_EQ(finalBomberYpos, expectedYpos);
}

TEST_CASE("Test if bomber can travel South Easterly")
{
	auto player = std::make_shared<Player>();
	auto bomber = std::make_shared<Bombers>(player);
	auto [xPlayerPos, yPlayerPos] = player->getPlayerPosition();
	auto [xBomberPos, yBomberPos] = bomber->getPosition();

	bomber->moveSouthEast(dt);

	auto [finalBomberXpos, finalBomberYpos] = bomber->getPosition();
	auto expectedYpos = yBomberPos + bomberSpeed * dt;
	auto expectedXpos = xBomberPos + bomberSpeed * dt;

	CHECK_EQ(finalBomberXpos, expectedXpos);
	CHECK_EQ(finalBomberYpos, expectedYpos);
}

TEST_CASE("Test if bomber can travel South Westerly")
{
	auto player = std::make_shared<Player>();
	auto bomber = std::make_shared<Bombers>(player);
	auto [xPlayerPos, yPlayerPos] = player->getPlayerPosition();
	auto [xBomberPos, yBomberPos] = bomber->getPosition();

	bomber->moveSouthWest(dt);

	auto [finalBomberXpos, finalBomberYpos] = bomber->getPosition();
	auto expectedYpos = yBomberPos + bomberSpeed * dt;
	auto expectedXpos = xBomberPos - bomberSpeed * dt;

	CHECK_EQ(finalBomberXpos, expectedXpos);
	CHECK_EQ(finalBomberYpos, expectedYpos);
}

TEST_CASE("Test if bomber can travel North Westerly")
{
	auto player = std::make_shared<Player>();
	auto bomber = std::make_shared<Bombers>(player);
	auto [xPlayerPos, yPlayerPos] = player->getPlayerPosition();
	auto [xBomberPos, yBomberPos] = bomber->getPosition();

	bomber->moveNorthWest(dt);

	auto [finalBomberXpos, finalBomberYpos] = bomber->getPosition();
	auto expectedYpos = yBomberPos - bomberSpeed * dt;
	auto expectedXpos = xBomberPos - bomberSpeed * dt;

	CHECK_EQ(finalBomberXpos, expectedXpos);
	CHECK_EQ(finalBomberYpos, expectedYpos);
}

//Bomber mine tests
TEST_CASE("Test if Bomber can place mine")
{
	auto xPosition = 100.0f;
	auto yPosition = 400.0f;
	auto mine = std::make_shared<Mine>(xPosition, yPosition);

	auto [xMinePos, yMinePos] = mine->getPosition();
	CHECK(xMinePos == xPosition);
	CHECK(yMinePos == yPosition);
}

TEST_CASE("Test if mine detonates after  10 seconds")
{
	std::vector<std::shared_ptr<Mine>>mines;
	std::vector<std::shared_ptr<MineSprite>>mine_sprites;

	auto xPosition = 150.0f;
	auto yPosition = 400.0f;
	auto mine = std::make_shared<Mine>(xPosition, yPosition);
	mines.push_back(mine);
	
	auto mine_sprite = std::make_shared<MineSprite>();
	mine_sprites.push_back(mine_sprite);

	auto timer = std::make_shared<StopWatch>();

	auto numberofMines = mines.size();
	auto numberOfMineSprites = mine_sprites.size();
	CHECK(numberofMines == numberOfMineSprites);
	CHECK(numberofMines == 1);

	//Fast forward to 10 seconds
	mine->test_updateMine(mines, mine_sprites, 10.0f);

	numberofMines = mines.size();
	numberOfMineSprites = mine_sprites.size();

	CHECK(numberofMines == numberOfMineSprites);
	CHECK(numberofMines == 0);
}

//Collision tests
TEST_CASE("Test for left horizontal collisions between any two entities")
{
	auto collisions = std::make_shared<Collisions>();
	auto object1Xposition = 100.0f;
	auto object1Yposition = 350.0f;
	auto object1Width = 20.0f;
	auto object1Length = 50.0f;

	auto object2Xposition = 40.0f;
	auto object2Yposition = 350.0f;
	auto object2Width = 20.0f;
	auto object2Length = 50.0f;

	auto isCollided = collisions->checkCollision(object1Xposition, object1Yposition, object1Width, object1Length,
		object2Xposition, object2Yposition, object2Width, object2Length);

	CHECK(isCollided == false);

	 //move second object towards first object such that the collide
	object2Xposition = 50.0f;

	isCollided = collisions->checkCollision(object1Xposition, object1Yposition, object1Width, object1Length,
		object2Xposition, object2Yposition, object2Width, object2Length);

	CHECK(isCollided == true);
}
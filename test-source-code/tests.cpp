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
auto upperBound = 10.0f;

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

	auto initial_direction = player->getDirection();
	auto left = true;
	auto right = false;
	auto up = false;
	auto down = false;
	auto space = false;
	auto gameOver = false;
	player->updatePlayer(left, right, up, down, space, player_sprite, laser_sprites, deltaTime, gameOver);

	auto final_direction = player->getDirection();

	//initial player direction should be to the right
	CHECK_EQ(initial_direction, initialPlayerDirection);
	//after user presses left arrow key, player direction should be to the left
	CHECK_EQ(final_direction, "left");

	//now user presses right
	right = true;
	left = false;
	player->updatePlayer(left, right, up, down, space, player_sprite, laser_sprites, deltaTime, gameOver);
	final_direction = player->getDirection();

	//The player should now face the right
	CHECK_EQ(final_direction, "right");
}

TEST_CASE("Test if player position is updated when user presses right arrow key")
{
	auto player = std::make_shared<Player>();
	auto player_sprite = std::make_shared<PlayerSprite>();
	std::vector<std::shared_ptr<LaserSprite>>laser_sprites;

	auto initial_direction = player->getDirection();
	auto left = false;
	auto right = true;
	auto up = false;
	auto down = false;
	auto space = false;
	auto gameOver = false;
	auto [initialXpos, initialYpos] = player->getPlayerPosition();
	player->updatePlayer(left, right, up, down, space, player_sprite, laser_sprites, deltaTime, gameOver);
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

	auto initial_direction = player->getDirection();
	auto left = true;
	auto right = false;
	auto up = false;
	auto down = false;
	auto space = false;
	auto gameOver = false;
	auto [initialXpos, initialYpos] = player->getPlayerPosition();
	player->updatePlayer(left, right, up, down, space, player_sprite, laser_sprites, deltaTime, gameOver);
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

	auto left = false;
	auto right = false;
	auto up = false;
	auto down = true;
	auto space = false;
	auto gameOver = false;
	deltaTime = 0.2f;
	auto [initialXpos, initialYpos] = player->getPlayerPosition();
	player->updatePlayer(left, right, up, down, space, player_sprite, laser_sprites, deltaTime, gameOver);
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

	auto left = false;
	auto right = false;
	auto up = true;
	auto down = false;
	auto space = false;
	auto gameOver = false;
	deltaTime = 0.2f;
	auto [initialXpos, initialYpos] = player->getPlayerPosition();
	player->updatePlayer(left, right, up, down, space, player_sprite, laser_sprites, deltaTime, gameOver);
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

	auto left = false;
	auto right = false;
	auto up = true; //will move 2500 units up
	auto down = false;
	auto space = false;
	auto gameOver = false;
	player->updatePlayer(left, right, up, down, space, player_sprite, laser_sprites, deltaTime, gameOver);
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

	auto left = false;
	auto right = false;
	auto up = false; 
	auto down = true;//will move 2500 units down
	auto space = false;
	auto gameOver = false;
	player->updatePlayer(left, right, up, down, space, player_sprite, laser_sprites, deltaTime, gameOver);
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

	auto left = false;
	auto right = true; //will move 2500 units right
	auto up = false;
	auto down = false;
	auto space = false;
	auto gameOver = false;
	player->updatePlayer(left, right, up, down, space, player_sprite, laser_sprites, deltaTime, gameOver);
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

	auto left = true; //will move 2500 units right
	auto right = false; 
	auto up = false;
	auto down = false;
	auto space = false;
	auto gameOver = false;
	player->updatePlayer(left, right, up, down, space, player_sprite, laser_sprites, deltaTime, gameOver);
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

	auto left = false;
	auto right = false;
	auto up = false;
	auto down = false;
	auto space = true;;
	auto gameOver = false;

	//no laser sprites prior space press
	CHECK(laser_sprites.empty() == true);
	player->updatePlayer(left, right, up, down, space, player_sprite, laser_sprites, deltaTime, gameOver);
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
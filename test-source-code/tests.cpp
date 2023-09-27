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
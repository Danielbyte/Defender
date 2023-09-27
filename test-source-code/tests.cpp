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
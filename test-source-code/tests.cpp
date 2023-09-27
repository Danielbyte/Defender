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
#include "stopWatch.h"

StopWatch::StopWatch():
	end_time {0.0f}
{
	start_time = current_time();
}

float StopWatch::current_time()
{
	auto time = clock();
	return static_cast<float>(time) / CLOCKS_PER_SEC;
}

float StopWatch::time_elapsed()
{
	stop();
	auto time_elapsed = end_time - start_time;
}

void StopWatch::stop()
{
	end_time = current_time();
}

void StopWatch::restart()
{
	start_time = current_time();
}

#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <ctime>

class StopWatch
{
public:
	StopWatch();
	float time_elapsed();
	void stop();
	void restart();

private:
	float current_time();
	float start_time;
	float end_time;
};
#endif // !STOPWATCH_H


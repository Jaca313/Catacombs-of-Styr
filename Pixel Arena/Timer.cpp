#include "Timer.h"

Timer::Timer()
{
	//Init new Clock
	clock = new sf::Clock();
	//Zero Internal Clock Times
	loopTime = 0.f;
	TotalTime = 0.f;
}

Timer::Timer(bool randomize)
{
	//Init new Clock
	clock = new sf::Clock();
	//Zero last frame time and randomize total time (used for animation)
	loopTime = 0.f;
	TotalTime = randomize ? (rand() % 3) * 1.f/3.f : 0.f;
}

float Timer::ResetClock()
{
	//Restarts Clock
	return clock->restart().asSeconds();
}

float Timer::Count()
{
	//Update Times
	loopTime = ResetClock();// Get last frame time
	TotalTime += loopTime;//Add frame time to Total Time
	return loopTime;//Return Last Frame Time
}

float Timer::rloopTime()
{
	return loopTime;//Get Last Frame Time
}

float Timer::rTotalTime()
{
	return TotalTime;//Get Total Elapsed Time
}

float Timer::rClearTotalTime()
{
	//Return Total Elapsed Time and Return it
	float returnValue = TotalTime;
	TotalTime = 0.f;
	return returnValue;
}

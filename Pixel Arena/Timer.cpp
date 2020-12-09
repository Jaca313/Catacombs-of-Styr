#include "Timer.h"

Timer::Timer()
{
	clock = new sf::Clock();
	loopTime = 0.f;
	TotalTime = 0.f;
}

Timer::Timer(bool randomize)
{
	clock = new sf::Clock();
	loopTime = 0.f;
	TotalTime = randomize ? (rand() % 3) * 1.0/3.0 : 0.f;
}

float Timer::ResetClock()
{
	return clock->restart().asSeconds();
}

float Timer::Count()
{
	loopTime = ResetClock();
	TotalTime += loopTime;
	return loopTime;
}



float Timer::rloopTime()
{
	return loopTime;
}

float Timer::rTotalTime()
{
	return TotalTime;
}

float Timer::rClearTotalTime()
{
	float returnValue = TotalTime;
	TotalTime = 0.f;
	return returnValue;
}

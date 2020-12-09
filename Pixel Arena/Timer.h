#pragma once
#include <SFML/System.hpp>
class Timer
{
	sf::Clock* clock;
	float TotalTime;
	float loopTime;
public:
	Timer();
	Timer(bool randomize);
	float Count();

	float rloopTime();
	float rTotalTime();
	float rClearTotalTime();
private:
	float ResetClock();
};


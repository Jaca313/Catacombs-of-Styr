#pragma once
#include <SFML/System.hpp>
class Timer
{
	sf::Clock* clock;
	double TotalTime;
	double loopTime;
public:
	Timer();
	Timer(bool randomize);
	float Count();

	float rloopTime();
	float rTotalTime();
private:
	float ResetClock();
};


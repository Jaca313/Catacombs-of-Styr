#pragma once
#include <SFML/System.hpp>
class Timer
{
	sf::Clock* clock;
	float TotalTime;
	float loopTime;
public:
	Timer();///<Start Timer
	Timer(bool randomize);///< Start Timer with a random offset
	float Count();///< Update Clocks

	float rloopTime();///< Returns time from last iteration/frame
	float rTotalTime();///< Returns total elapsed time
	float rClearTotalTime();///< Resets total elapsed time
private:
	float ResetClock();///< Internal "Restart clock"/ returns last iter time
};


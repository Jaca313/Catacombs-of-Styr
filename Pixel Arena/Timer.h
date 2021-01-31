#pragma once
#include <SFML/System.hpp>
class Timer///< Timer Class
{
	sf::Clock* clock;///< SFML Clock for timekeeping
	float TotalTime;///< Total Elapsed time since start of clock
	float loopTime;///< Time since last Frame
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


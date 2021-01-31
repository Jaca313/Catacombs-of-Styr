#include "LogManager.h"

char* LogManager::GetTime()
{
	//Gets System Time
	auto fTime = std::chrono::system_clock::now();
	std::time_t Time = std::chrono::system_clock::to_time_t(fTime);
	return std::ctime(&Time);
}

void LogManager::LOG(int level, std::string message)
{
	//Logs messages according to log level
	if (level >= LogLevel)
	{
		INFO << "///////////////////////////////////////////////////" << std::endl;
		INFO << GetTime();// << std::endl;
		INFO << message << std::endl;
	}
}

void LogManager::ERR(int level, std::string error)
{
	//Logs errors according to log level
	if (level >= LogLevel)
	{
		ERROR << "///////////////////////////////////////////////////" << std::endl;
		ERROR << GetTime();// << std::endl;
		ERROR << error << std::endl;
	}
}

float LogManager::FixAngle(float Ang)
{
	//Binds angles (in Deg) to 0-359
	if (Ang > 359)Ang -= 360;
	if (Ang < 0)Ang += 360;
	return Ang;
}

float LogManager::DegtoRad(float Deg)
{
	//Changes Degrees to Radians
	return (float)Deg * C_PI  / 180.f;
}

float LogManager::RadtoDeg(float Rad)
{
	//Changes Radians to Degrees
	return float(Rad * 180 / C_PI);
}

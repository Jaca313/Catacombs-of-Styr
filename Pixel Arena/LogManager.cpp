#include "LogManager.h"

char* LogManager::GetTime()
{
	auto fTime = std::chrono::system_clock::now();
	std::time_t Time = std::chrono::system_clock::to_time_t(fTime);
	return std::ctime(&Time);
}

void LogManager::LOG(int level, std::string message)
{
	if (level >= LogLevel)
	{
		INFO << "///////////////////////////////////////////////////" << std::endl;
		INFO << GetTime();// << std::endl;
		INFO << message << std::endl;
	}
}

void LogManager::ERR(int level, std::string error)
{
	if (level >= LogLevel)
	{
		ERROR << "///////////////////////////////////////////////////" << std::endl;
		ERROR << GetTime();// << std::endl;
		ERROR << error << std::endl;
	}
}

float LogManager::FixAngle(float Ang)
{
	if (Ang > 359)Ang -= 360;
	if (Ang < 0)Ang += 360;
	return Ang;
}

float LogManager::DegtoRad(float Deg)
{
	return (float)Deg * C_PI / 180.f;
}

float LogManager::RadtoDeg(float Rad)
{
	return float(Rad * 180 / C_PI);
}

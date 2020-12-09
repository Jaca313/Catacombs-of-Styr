#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>

#define C_PI 3.1415923565

const float c_Fov = 90.f;

class LogManager
{
	////////////////////////////////////////////////////////////////////////////////
	//									Init/Core
	////////////////////////////////////////////////////////////////////////////////
private:
	LogManager() {

		INFO.open("Log/Log.txt", std::ofstream::app);
		ERROR.open("Log/Error.txt", std::ofstream::app);
	}
	~LogManager() {

		INFO.close();
		ERROR.close();

	}
public:
	static LogManager& getInstance() {
		static LogManager theInstance;
		return theInstance;
	}
	////////////////////////////////////////////////////////////////////////////////
	//									Resources
	////////////////////////////////////////////////////////////////////////////////
private:
	std::ofstream INFO;
	std::ofstream ERROR;

	int LogLevel = 1;

	////////////////////////////////////////////////////////////////////////////////
	//                         Functionality
	////////////////////////////////////////////////////////////////////////////////
private:
	char* GetTime();


public:
	void LOG(int level, std::string message);

	void ERR(int level, std::string error);


	//Helpers
	static float FixAngle(float Ang);
	static float DegtoRad(float Deg);
	static float RadtoDeg(float Rad);


};


#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>

#define C_PI 3.1415923565f
const float c_Fov = 90.f;
//HACK: Currently a mishmash for global access stuff and Output logs


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
	///<Singleton Implementation
	static LogManager& getInstance() {
		static LogManager theInstance;
		return theInstance;
	}
	////////////////////////////////////////////////////////////////////////////////
	//									Resources
	////////////////////////////////////////////////////////////////////////////////
private:
	std::ofstream INFO;///<Info file stream
	std::ofstream ERROR;///<Error file stream

	int LogLevel = 1;///< What level to log stuff into files(cutoff)
	////////////////////////////////////////////////////////////////////////////////
	//                         Functionality
	////////////////////////////////////////////////////////////////////////////////
private:
	char* GetTime();///<Return System Time for logging purposes


public:
	void LOG(int level, std::string message);///<Logs into Info File and Console
	void ERR(int level, std::string error);///<Logs into Error File and Console


	//Helpers
	static float FixAngle(float Ang);///<Helper (mainly Gamestate) Fixes Angles out of Range(0,359)
	static float DegtoRad(float Deg);///<Helper (mainly Gamestate) Degrees to Radian
	static float RadtoDeg(float Rad);///<Helper (mainly Gamestate) Radian to Degrees

};


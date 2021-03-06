#pragma once
#include "State_Gameplay.h"
#include "State_MainMenu.h"
#include "State_Pause.h"
#include "State_Editor.h"
#include <iostream>
#include <stack>
#include <fstream>
#include <string>

#include "ResourceManager.h"

class PixelArena///< Main App Class
{
public:
	PixelArena();///< Default Constructor with Setup
	~PixelArena();///<Destructor (cleans up window and exits execution stack in order)
public:
	void Run();///< Main App Entry Point with Setup and Loop
private:
	//Drawing
	void LoadSettings();///< Loads Window Height and Width from window.ini
	std::wstring m_winName;///< Window Title from window.ini
	int m_winWidth;///< Window Width from window.ini
	int m_winHeight;///< Window Height from window.ini
	sf::RenderWindow* m_window;///< Window to be drawn to

	sf::RenderTexture m_screenBuffer;///< Intermediary buffer to be drawn to (used  for intermediary shader use)
	void InitTextures();///< Used to initialize m_screenBuffer

	//Execution
	std::stack<GameState*> m_executionStack;///< Stack for Gamestates
	void MainLoop();///< Main loop

	//Managers
	LogManager& InfoTool = LogManager::getInstance();/// Utility Class
	ResourceManager& Resources = ResourceManager::getInstance();/// Resource Class

	//Timekeeping
	Timer m_cClock;///Calculates frametime
	float m_fTime = 1/60.f;/// Time between frames

	void PopState();///< Lets the State finish and removes it from stack
	void PushState(int _requestedState);///< Lets a state push a new Gamestate to stack

	void ExitGame();///< Closes Window
};


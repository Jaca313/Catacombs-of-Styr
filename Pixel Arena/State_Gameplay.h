#pragma once
#include "GameState.h"
#include "InGameUI.h"
#include "LevelMap.h"
#include "Player.h"
#include <limits.h>
#include "Timer.h"
#include "ResourceManager.h"
#include "EntityManager.h"


class State_Gameplay :
	public GameState
{
public:
	State_Gameplay(sf::RenderWindow* pWindow, ResourceManager* Resources );
private:
	sf::RenderWindow* Window;
	sf::RenderTexture* ScreenBuffer;
public:
	void EventLoop();
	void Input(double fTime);
	void Update(double fTime);
	void Draw(sf::RenderTexture* ScreenBuffer);

//Resources
private:
	LevelMap Level;
	Player* Butcher;

	ResourceManager* Resources;
	EntityManager& Entities = EntityManager::getInstance();
	LogManager& Info = LogManager::getInstance();

	InGameUI UI = InGameUI();
	
	//Camera Settings
	double fov = c_Fov;//Optimized for 90 btw
	double distancetoProj = 0;//Calculated at Construction
	double* Z_Buffer; // (distance to the nearest wall in that pixel)
	//Drawing
	void CastRaysFloorCeil();
	void CastRays3DWalls();

	void DrawUI();
	void DrawEntities();

	void Fill_Z_Buffer();

};


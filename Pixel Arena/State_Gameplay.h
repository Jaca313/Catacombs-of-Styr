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
	~State_Gameplay();
private:
	sf::RenderWindow* Window;///< Final Output
	sf::RenderTexture* ScreenBuffer;///< Intermediary drawing target for shader use
public:
	void eventLoop();///< Queries and resolves SFML events
	void input(double fTime);///< User Input (Keyboard and Mouse)
	void update(double fTime);///< Calculates Internal Resource Changes
	void draw(sf::RenderTexture* ScreenBuffer);///< Outputs Elements to ScreenBuffer

//Resources
private:
	LevelMap Level;///< Contains Level Data
	Player* Butcher;///< Pointer to Player

	ResourceManager* Resources;///< Pointer to Resources
	EntityManager& Entities = EntityManager::getInstance();///< Reference to Entities
	LogManager& Info = LogManager::getInstance();///< Reference to Internal Messaging

	InGameUI UI = InGameUI();///< Ingame UI Elements
	
	//Camera Settings
	double m_cFov = c_Fov;///< Previously changeable now permanently set to 90(deg)
	double m_cdistancetoProj = 0;///< Distance from the camera to projected screen
	double* Z_Buffer;///< Depth Buffer
	//Drawing
	void CastRaysFloorCeil();
	void CastRays3DWalls();

	void DrawUI();
	void DrawEntities();

	void Fill_Z_Buffer();

};


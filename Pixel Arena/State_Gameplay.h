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
	public GameState ///< GamePlay GameState
{
public:
	State_Gameplay(sf::RenderWindow* _pWindow, ResourceManager* _Resources );///< Setup State
	~State_Gameplay();///< Destroy Player and Z_Buffer
private:
	sf::RenderWindow* Window;///< Final Output
	sf::RenderTexture* ScreenBuffer;///< Intermediary drawing target for shader use
public:
	void eventLoop();///< Queries and resolves SFML events
	void input(float _fTime);///< User Input (Keyboard and Mouse)
	void update(float _fTime);///< Calculates Internal Resource Changes
	void draw(sf::RenderTexture* _ScreenBuffer);///< Outputs Elements to ScreenBuffer

	void resumeState();///< When a state is resumed
//Resources
private:
	LevelMap Level;///< Contains Level Data
	Player* Butcher;///< Pointer to Player

	ResourceManager* Resources;///< Pointer to Resources
	EntityManager& Entities = EntityManager::getInstance();///< Reference to Entities
	LogManager& Info = LogManager::getInstance();///< Reference to Internal Messaging

	InGameUI UI = InGameUI();///< Ingame UI Elements
	
	//Camera Settings
	float m_cFov = c_Fov;///< Previously changeable now permanently set to 90(deg)
	float m_cdistancetoProj = 0;///< Distance from the camera to projected screen
	float* m_sZ_Buffer;///< Depth Buffer
	//Drawing
	void CastRaysFloorCeil();///< Draws Affine Mapping of Floor and Ceiling
	void CastRays3DWalls();///< Draws Raycasted screen projection from Camera

	void DrawUI();///< Draws Ingame UI
	void DrawEntities();///< Draws Entities in GameWorld

	void Fill_Z_Buffer();///< Codes values from depthbuffer onto Texture

};


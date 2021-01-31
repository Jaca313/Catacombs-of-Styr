#pragma once
#include "GameState.h"
#include "ResourceManager.h"
#include "Scene_MainMenu.h"
#include "Scene_Help.h"
#include "Scene_Options.h"
class State_MainMenu :	public GameState///< MainMenu GameState
{
public:
	State_MainMenu(sf::RenderWindow* pWindow, ResourceManager* Resources);///< Setup State and Scenes
	~State_MainMenu();///< Cleanup Scenes
private:
	sf::RenderWindow* Window;///< Final Output
	sf::RenderTexture* ScreenBuffer;///< Intermediary drawing target for shader use
public:
	void eventLoop();///< Queries and resolves SFML events
	void input(float _fTime);///< User Input (Keyboard and Mouse)
	void update(float _fTime);///< Calculates Internal Resource Changes
	void draw(sf::RenderTexture* _ScreenBuffer);///< Outputs Elements to ScreenBuffer

	void resumeState();///< When a state is resumed

private:
	sf::RectangleShape m_sBackground;///< MainMenu Background Image

//Resources
private:
	ResourceManager* Resources;///< Pointer to Resources
	LogManager& Info = LogManager::getInstance();///< Reference to Internal Messaging

	void SetupBackground();///<Loads Background from Resource Manager 

	std::map<std::string, Scene*> Scenes;///< Map of Available Scenes
	Scene* pCurrentScene = nullptr;///< pointer to Current Scene
	int eCurrentScene = 0;///< Enum of Current scene
	void SetupCursor();///< Sets correct cursor for mouse 
};


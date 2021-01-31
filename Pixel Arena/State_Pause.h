#pragma once
#include "GameState.h"
#include "ResourceManager.h"
#include "Scene_Pause.h"
class State_Pause : public GameState ///< Pause GameState ingame
{
public:
	State_Pause(sf::RenderWindow* _pWindow, ResourceManager* _Resources);///< Setup State and Scene
	~State_Pause();///< Cleanup Scenes and Background
private:
	sf::RenderWindow* Window;///< Final Output
	sf::RenderTexture* ScreenBuffer;///< Intermediary drawing target for shader use
	sf::Texture* GameBackground = nullptr;///< Background (Paused Previous GameState Buffer)
public:
	void eventLoop();///< Queries and resolves SFML events
	void input(float _fTime);///< User Input (Keyboard and Mouse)
	void update(float _fTime);///< Calculates Internal Resource Changes
	void draw(sf::RenderTexture* _ScreenBuffer);///< Outputs Elements to ScreenBuffer

	void resumeState();///< When a state is resumed
	void endState();///< When a state is exiting
private:
	sf::RectangleShape m_sBackground;///< Background (copy of GameBackround stretched to current window)

	//Resources
private:
	ResourceManager* Resources;///< Pointer to Resources
	LogManager& Info = LogManager::getInstance();///< Reference to Internal Messaging

	void SetupBackground();///< Setup m_sBackground as a copy of GameBackground

	std::map<std::string, Scene*> Scenes;///< Contains all scenes in GameState
	Scene* pCurrentScene = nullptr;///< pointer to Currently rendered scene
	int eCurrentScene = 0;///< enum of current Scene
	void SetupCursor();///< Sets correct cursor for mouse 
};


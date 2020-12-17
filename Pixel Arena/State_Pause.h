#pragma once
#include "GameState.h"
#include "ResourceManager.h"
#include "Scene_Pause.h"
class State_Pause : public GameState
{
public:
	State_Pause(sf::RenderWindow* _pWindow, ResourceManager* _Resources);
	~State_Pause();
private:
	sf::RenderWindow* Window;///< Final Output
	sf::RenderTexture* ScreenBuffer;///< Intermediary drawing target for shader use
	sf::Texture* GameBackground = nullptr;
public:
	void eventLoop();///< Queries and resolves SFML events
	void input(float _fTime);///< User Input (Keyboard and Mouse)
	void update(float _fTime);///< Calculates Internal Resource Changes
	void draw(sf::RenderTexture* _ScreenBuffer);///< Outputs Elements to ScreenBuffer

	void resumeState();///< When a state is resumed
	void endState();
private:
	sf::RectangleShape m_sBackground;

	//Resources
private:
	ResourceManager* Resources;///< Pointer to Resources
	LogManager& Info = LogManager::getInstance();///< Reference to Internal Messaging

	void SetupBackground();

	std::map<std::string, Scene*> Scenes;
	Scene* pCurrentScene = nullptr;
	int eCurrentScene = 0;
	void SetupCursor();
};


#pragma once
#include "GameState.h"
#include "ResourceManager.h"
class State_MainMenu :	public GameState
{
public:
	State_MainMenu(sf::RenderWindow* pWindow, ResourceManager* Resources);
	~State_MainMenu();
private:
	sf::RenderWindow* Window;///< Final Output
	sf::RenderTexture* ScreenBuffer;///< Intermediary drawing target for shader use
public:
	void eventLoop();///< Queries and resolves SFML events
	void input(float _fTime);///< User Input (Keyboard and Mouse)
	void update(float _fTime);///< Calculates Internal Resource Changes
	void draw(sf::RenderTexture* _ScreenBuffer);///< Outputs Elements to ScreenBuffer

private:
	sf::RectangleShape Background;

//Resources
private:
	ResourceManager* Resources;///< Pointer to Resources
	LogManager& Info = LogManager::getInstance();///< Reference to Internal Messaging

};


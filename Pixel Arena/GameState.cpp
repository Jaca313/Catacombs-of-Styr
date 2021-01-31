#include "GameState.h"

GameState::~GameState()
{
	//overwrite in derived
}

bool GameState::quitState() const
{
	//overwrite in derived
	//check if state wants to quit
	return m_bWantsQuit;
}

int GameState::requestState()
{
	//overwrite in derived
	//Request another state to be pushed and set to be resumed
	int returnValue = m_iRequestState;
	m_iRequestState = 0;
	m_bResume = 1;
	return returnValue;
}

void GameState::resumeState()
{
	//overwrite in derived
	//resume state
	m_bResume = false;
}

int GameState::forceState() const
{
	//overwrite in derived
	//set demand to force exit to an exact state lower in stack
	return m_bForceState;
}

void GameState::endState()
{
	//overwrite in derived
	//What to do when state ends operation(saving, setting vars etc.)
}

void GameState::updateMousePos(sf::RenderWindow* _Window)
{
	//Update mouse position (Global,Window,View)
	m_vMousePosGlobal = sf::Mouse::getPosition();
	m_vMousePosWindow = sf::Mouse::getPosition(*_Window);
	m_vMousePosView = _Window->mapPixelToCoords(sf::Mouse::getPosition(*_Window));
}

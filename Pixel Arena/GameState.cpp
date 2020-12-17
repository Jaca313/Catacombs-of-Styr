#include "GameState.h"

GameState::~GameState()
{
}

bool GameState::quitState() const
{
	return m_bWantsQuit;
}

int GameState::requestState()
{
	int returnValue = m_iRequestState;
	m_iRequestState = 0;
	m_bResume = 1;
	return returnValue;
}

void GameState::resumeState()
{
	m_bResume = false;
}

int GameState::forceState() const
{
	return m_bForceState;
}

void GameState::endState()
{
}

void GameState::updateMousePos(sf::RenderWindow* _Window)
{
	m_vMousePosGlobal = sf::Mouse::getPosition();
	m_vMousePosWindow = sf::Mouse::getPosition(*_Window);
	m_vMousePosView = _Window->mapPixelToCoords(sf::Mouse::getPosition(*_Window));
}

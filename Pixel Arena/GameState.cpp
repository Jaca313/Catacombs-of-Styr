#include "GameState.h"

bool GameState::quitState() const
{
	return m_bWantsQuit;
}

int GameState::requestState()
{
	int returnValue = m_iRequestState;
	m_iRequestState = 0;
	return returnValue;
}

void GameState::endState()
{
}

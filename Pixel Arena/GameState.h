#pragma once

class GameState
{
public:
	int ID = 0;///< Id of State
	virtual void eventLoop() = 0;///< Overwrite SFML event Loop
	virtual void input(float fTime) = 0;///< Overwrite User Input
	virtual void update(float fTime) = 0;///< Overwrite Update Cycle
	virtual void draw(sf::RenderTexture* ScreenBuffer) = 0;///< Draws to Buffer

	virtual bool quitState() const;///< Check if State wants to quit
	bool m_bWantsQuit = 0;///< bool if state is quitting
	virtual int requestState();///< checks if state wants to push another state to stack
	int m_iRequestState = 0;///< requested state
	virtual void resumeState();///< operation when resuming state
	bool m_bResume = 0;///< bool if state is to be resumed

	virtual void endState();///< Final saving / operations when exiting from state

	sf::Vector2i m_vMousePosGlobal;///<Mouse position in relation to Screen
	sf::Vector2i m_vMousePosWindow;///<Mouse position in relation to window
	sf::Vector2f m_vMousePosView;///<Mouse position in relation to view

	void updateMousePos(sf::RenderWindow* _Window);///< updates mouse position
};


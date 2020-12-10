#pragma once

class GameState
{
public:
	int ID = 0;///< Id of State
	virtual void eventLoop() = 0;///< Overwrite SFML event Loop
	virtual void input(float fTime) = 0;///< Overwrite User Input
	virtual void update(float fTime) = 0;///< Overwrite Update Cycle
	virtual void draw(sf::RenderTexture* ScreenBuffer) = 0;///< Draws to Buffer

	virtual bool quitState() const;
	bool m_bWantsQuit = 0;
	virtual int requestState();
	int m_iRequestState = 0;

	virtual void endState();

	sf::Vector2i m_vMousePosGlobal;///<Mouse position in relation to Screen
	sf::Vector2i m_vMousePosWindow;///<Mouse position in relation to window
	sf::Vector2f m_vMousePosView;///<Mouse position in relation to view

	void updateMousePos(sf::RenderWindow* _Window);///< updates mouse position
};


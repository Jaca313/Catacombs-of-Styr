#pragma once

class GameState
{
public:
	int ID = 0;///< Id of State
	virtual void eventLoop() = 0;///< Overwrite SFML event Loop
	virtual void input(float fTime) = 0;///< Overwrite User Input
	virtual void update(float fTime) = 0;///< Overwrite Update Cycle
	virtual void draw(sf::RenderTexture* ScreenBuffer) = 0;///< Draws to Buffer
};


#pragma once

class GameState
{
public:
	int ID = 0;
	virtual void EventLoop() = 0;
	virtual void Input(double fTime) = 0;
	virtual void Update(double fTime) = 0;
	virtual void Draw(sf::RenderTexture* ScreenBuffer) = 0;
	//display will be in main loop
};


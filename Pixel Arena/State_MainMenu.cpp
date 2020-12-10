#include "stdafx.h"
#include "State_MainMenu.h"

State_MainMenu::State_MainMenu(sf::RenderWindow* _Window, ResourceManager* _Resources)
{
	//Basic Setup
	this->ID = 200;
	this->Window = _Window;
	//Window->setMouseCursorVisible(false);
	Window->setVerticalSyncEnabled(true);
	//Link Resources
	this->Resources = _Resources;

}

State_MainMenu::~State_MainMenu()
{
	//Cleanup

}


void State_MainMenu::eventLoop()
{
	sf::Event event;
	while (this->Window->pollEvent(event))
	{
		//Close Window
		if (event.type == sf::Event::Closed)
			this->Window->close();
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			this->Window->close();
	}
}

void State_MainMenu::input(float _fTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N)) {
		m_iRequestState = eGameplay;;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J)) {
		m_bWantsQuit = true;
	}
}

void State_MainMenu::update(float _fTime)
{

}

void State_MainMenu::draw(sf::RenderTexture* _ScreenBuffer)
{
	this->ScreenBuffer = _ScreenBuffer;

	this->ScreenBuffer->clear(sf::Color(120, 120, 120, 255));//Clear Buffer


}


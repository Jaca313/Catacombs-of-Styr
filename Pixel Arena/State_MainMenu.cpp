#include "stdafx.h"
#include "State_MainMenu.h"

State_MainMenu::State_MainMenu(sf::RenderWindow* _Window, ResourceManager* _Resources)
{
	//Basic Setup
	this->ID = 200;
	this->Window = _Window;
	Window->setMouseCursorVisible(true);
	Window->setVerticalSyncEnabled(true);
	//Link Resources
	this->Resources = _Resources;





	SetupBackground();


	Scenes.insert(std::pair<std::string, Scene*>(std::string("Main_Menu"), (Scene*)new Scene_MainMenu()));
	CurrentScene = Scenes.at("Main_Menu");
}

State_MainMenu::~State_MainMenu()
{
	//Cleanup
	for (auto Sc : Scenes) {
		delete Sc.second;
	}

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

	ScreenBuffer->draw(m_sBackground,m_sBackground.getTexture());

	CurrentScene->drawScene(*_ScreenBuffer);
}

void State_MainMenu::resumeState()
{
	m_bResume = false;
	Window->setMouseCursorVisible(true);
}

void State_MainMenu::SetupBackground()
{
	m_sBackground.setPosition(0.f, 0.f);
	m_sBackground.setSize(sf::Vector2f((float)Window->getSize().x, (float)Window->getSize().y));
	m_sBackground.setTexture(Resources->getTex(29));//Main Menu Background
}


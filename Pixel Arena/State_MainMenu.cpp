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
	Scenes.insert(std::pair<std::string, Scene*>(std::string("Options"), (Scene*)new Scene_Options()));
	Scenes.insert(std::pair<std::string, Scene*>(std::string("Help"), (Scene*)new Scene_Help()));

	pCurrentScene = Scenes.at("Main_Menu");
	eCurrentScene = Scenes::Main_Menu;
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
		//if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
		//	this->Window->close();

		if (event.type == sf::Event::MouseEntered) {
			SetupCursor();
		}

	}
}

void State_MainMenu::input(float _fTime)
{
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N)) {
	//	m_iRequestState = eGameplay;;
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::J)) {
	//	m_bWantsQuit = true;
	//}

	//CHeck what scene it is switch or something then

	switch (eCurrentScene) {
		case Scenes::Main_Menu: {
			if (Scenes.at("Main_Menu")->Buttons.at("Start").isReleased()) {
				m_iRequestState = eGameplay;
			}
			if (Scenes.at("Main_Menu")->Buttons.at("Options").isReleased()) {
				eCurrentScene = Scenes::Options;
				pCurrentScene = Scenes.at("Options");
			}
			if (Scenes.at("Main_Menu")->Buttons.at("Help").isReleased()) {
				eCurrentScene = Scenes::Help;
				pCurrentScene = Scenes.at("Help");
			}
			if (Scenes.at("Main_Menu")->Buttons.at("Quit").isReleased()) {
				m_bWantsQuit = true;
			}
			break;
		}
		case Scenes::Help: {
			if (Scenes.at("Help")->Buttons.at("Return").isReleased()) {
				eCurrentScene = Scenes::Main_Menu;
				pCurrentScene = Scenes.at("Main_Menu");
			}
			break;
		}
		case Scenes::Options: {

			break;
		}
	}

}

void State_MainMenu::update(float _fTime)
{
	updateMousePos(Window);
	pCurrentScene->updateButtons(m_vMousePosView);
}

void State_MainMenu::draw(sf::RenderTexture* _ScreenBuffer)
{
	this->ScreenBuffer = _ScreenBuffer;

	this->ScreenBuffer->clear(sf::Color(120, 120, 120, 255));//Clear Buffer

	ScreenBuffer->draw(m_sBackground,m_sBackground.getTexture());

	pCurrentScene->drawScene(*_ScreenBuffer);
}

void State_MainMenu::resumeState()
{
	m_bResume = false;
	Window->setMouseCursorVisible(true);

	//Cursor is copied
	SetupCursor();
}

void State_MainMenu::SetupBackground()
{
	m_sBackground.setPosition(0.f, 0.f);
	m_sBackground.setSize(sf::Vector2f((float)Window->getSize().x, (float)Window->getSize().y));
	m_sBackground.setTexture(Resources->getTex(29));//Main Menu Background
}

void State_MainMenu::SetupCursor()
{
	//Cursor is copied
	sf::Image im_cursor;
	im_cursor.loadFromFile("Textures/GUI/Cursor.png");;
	sf::Cursor Cursor;
	Cursor.loadFromPixels(im_cursor.getPixelsPtr(), sf::Vector2u(im_cursor.getSize().x, im_cursor.getSize().y), sf::Vector2u(18, 15));
	Window->setMouseCursor(Cursor);
}


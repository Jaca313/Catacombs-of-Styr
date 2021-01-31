#include "stdafx.h"
#include "State_Pause.h"

State_Pause::State_Pause(sf::RenderWindow* _pWindow, ResourceManager* _Resources)
{
	//Basic Setup
	this->ID = 300;
	this->Window = _pWindow;
	Window->setMouseCursorVisible(true);
	Window->setVerticalSyncEnabled(true);
	//Link Resources
	this->Resources = _Resources;

	//Push Pause Scene
	Scenes.insert(std::pair<std::string, Scene*>(std::string("Pause"), (Scene*)new Scene_Pause()));

	//Set Current Scene to Pause
	pCurrentScene = Scenes.at("Pause");
	eCurrentScene = Scenes::Pause;
}

State_Pause::~State_Pause()
{
	//Cleanup of Scenes
	for (auto& Sc : Scenes) {
		delete Sc.second;
	}
	//Cleanup pointer to Previous Saved ScreenBuffer
	delete GameBackground;
}

void State_Pause::eventLoop()
{
	//Handel SFML Events
	sf::Event event;
	while (this->Window->pollEvent(event))
	{
		//Close Window
		if (event.type == sf::Event::Closed)
			this->Window->close();
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			m_bWantsQuit = true;

		//Set correct cursor when entering window
		if (event.type == sf::Event::MouseEntered) {
			SetupCursor();
		}

	}
}

void State_Pause::input(float _fTime)
{
	//Resolve Buttons in Scene
	switch (eCurrentScene) {
	case Scenes::Pause: {
		if (Scenes.at("Pause")->Buttons.at("Resume").isReleased()) {
			m_bWantsQuit = true;
		}
		if (Scenes.at("Pause")->Buttons.at("ExitMenu").isReleased()) {
			m_bForceState = 200;
		}
		if (Scenes.at("Pause")->Buttons.at("Quit").isReleased()) {
			m_bForceState = 0;
		}
		break;
	}
}
}

void State_Pause::update(float _fTime)
{
	//Update Mouse Position
	updateMousePos(Window);
	//Update Buttons
	pCurrentScene->updateButtons(m_vMousePosView);

}

void State_Pause::draw(sf::RenderTexture* _ScreenBuffer)
{
	//if first entering save ScreenBuffer
	if(!GameBackground)GameBackground = new sf::Texture(_ScreenBuffer->getTexture());
	SetupBackground();//Get Copy of GameBackground to m_sBackground

	//Set and Clear ScreenBuffer
	this->ScreenBuffer = _ScreenBuffer;
	this->ScreenBuffer->clear(sf::Color(120, 120, 120, 255));//Clear Buffer

	//Set Uniforms for Blur Shader and render Background
	Resources->m_sFlipScreenBlur.setUniform("iResolution", sf::Vector2f(Window->getSize().x, Window->getSize().y));
	ScreenBuffer->draw(m_sBackground,&Resources->m_sFlipScreenBlur);

	//Render Current Scene
	pCurrentScene->drawScene(*_ScreenBuffer);
}

void State_Pause::resumeState()
{
	//if Returning to this scene 
	m_bResume = false;//set have already resumed
	Window->setMouseCursorVisible(true);//set mouse visible

	//Set Cursor
	SetupCursor();
}

void State_Pause::endState()
{
	//if exiting set Mouse to the middle of Screen
	sf::Mouse::setPosition(sf::Vector2i(Window->getSize().x / 2, Window->getSize().y / 2), *Window);
}

void State_Pause::SetupBackground()
{
	//Setup Background (Saved Previous GameState ScreenBuffer)
	m_sBackground.setPosition(0.f, 0.f);
	m_sBackground.setSize(sf::Vector2f((float)Window->getSize().x, (float)Window->getSize().y));
	m_sBackground.setTexture(GameBackground);//Main Menu Background
}

void State_Pause::SetupCursor()
{
	//Set Mouse Cursor
	//Cursor is copied
	sf::Image im_cursor;
	im_cursor.loadFromFile("Textures/GUI/Cursor.png");
	sf::Cursor Cursor;
	Cursor.loadFromPixels(im_cursor.getPixelsPtr(), sf::Vector2u(im_cursor.getSize().x, im_cursor.getSize().y), sf::Vector2u(18, 15));
	Window->setMouseCursor(Cursor);
}

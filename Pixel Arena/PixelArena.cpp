#include "PixelArena.h"

PixelArena::PixelArena()
{
	LoadSettings();

	this->m_window = new sf::RenderWindow(sf::VideoMode(m_winWidth, m_winHeight), m_winName);
	m_window->setVerticalSyncEnabled(false);

	InitTextures();
}

PixelArena::~PixelArena()
{
	delete m_window;
}

void PixelArena::Run()
{
	m_executionStack.push(new State_Gameplay(m_window,&Resources));
	MainLoop();
}

void PixelArena::LoadSettings()
{
	//Default Values
	m_winWidth = 800;
	m_winHeight = 600;

	m_winName = L"Default";

	//Grabs Setting from File
	std::wifstream ifs("Config/Window.ini");
	if (ifs.is_open())
	{
		std::getline(ifs, m_winName);
		ifs >> m_winWidth >> m_winHeight;
	}
	ifs.close();

}

void PixelArena::MainLoop()
{
	while (m_window->isOpen()) {

		m_executionStack.top()->eventLoop();
		m_executionStack.top()->input(m_fTime);
		m_executionStack.top()->update(m_fTime);
		m_executionStack.top()->draw(&m_screenBuffer);
		//Display
		m_window->draw(sf::Sprite(m_screenBuffer.getTexture()),&Resources.m_sFlipScreen);
		m_window->display();

		//Timing
		m_fTime = m_cClock.Count();
	}

}

void PixelArena::InitTextures()
{
	if (!m_screenBuffer.create(m_winWidth, m_winHeight)) {
		std::string Error = "Could not Create m_screenBuffer";
		InfoTool.ERR(5, Error);
	}
}


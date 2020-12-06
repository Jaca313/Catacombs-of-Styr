#include "PixelArena.h"

PixelArena::PixelArena()
{
	LoadSettings();

	this->Window = new sf::RenderWindow(sf::VideoMode(m_winWidth, m_winHeight), m_winName);
	Window->setVerticalSyncEnabled(false);

	InitTextures();
}

PixelArena::~PixelArena()
{
}

void PixelArena::Run()
{
	m_executionStack.push(new State_Gameplay(Window,&Resources));
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
	while (Window->isOpen()) {

		m_executionStack.top()->EventLoop();
		m_executionStack.top()->Input(m_fTime);
		m_executionStack.top()->Update(m_fTime);
		m_executionStack.top()->Draw(&m_screenBuffer);
		//Display
		Window->draw(sf::Sprite(m_screenBuffer.getTexture()),&Resources.m_sFlipScreen);
		Window->display();

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


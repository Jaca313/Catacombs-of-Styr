#include "PixelArena.h"

PixelArena::PixelArena()
{
	LoadSettings();

	this->m_window = new sf::RenderWindow(sf::VideoMode(m_winWidth, m_winHeight), m_winName, sf::Style::Titlebar | sf::Style::Close );
	m_window->setVerticalSyncEnabled(false);

	//Icon is copied no need for it to hang around
	sf::Image icon;
	icon.loadFromFile("Textures/GUI/Icon.png");;
	m_window->setIcon(icon.getSize().x,icon.getSize().y,icon.getPixelsPtr());
	//Cursor is copied
	sf::Image im_cursor;
	im_cursor.loadFromFile("Textures/GUI/Cursor.png");;
	sf::Cursor Cursor;
	Cursor.loadFromPixels(im_cursor.getPixelsPtr(), sf::Vector2u(im_cursor.getSize().x, im_cursor.getSize().y), sf::Vector2u(0.0, 0.0));
	m_window->setMouseCursor(Cursor);


	InitTextures();
}

PixelArena::~PixelArena()
{
	delete m_window;

	while (!m_executionStack.empty()) {
		delete m_executionStack.top();
		m_executionStack.pop();
	}
}

void PixelArena::Run()
{
	//m_executionStack.push(new State_Gameplay(m_window,&Resources));
	m_executionStack.push(new State_MainMenu(m_window, &Resources));
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
	while (m_window->isOpen() && !m_executionStack.empty()) {

		if (m_executionStack.top()->m_bResume)m_executionStack.top()->resumeState();

		m_executionStack.top()->eventLoop();
		m_executionStack.top()->input(m_fTime);
		m_executionStack.top()->update(m_fTime);
		m_executionStack.top()->draw(&m_screenBuffer);
		//Display
		m_window->draw(sf::Sprite(m_screenBuffer.getTexture()), &Resources.m_sFlipScreen);
		m_window->display();

		//Timing
		m_fTime = m_cClock.Count();

		//GameState Controller
		if (m_executionStack.top()->m_iRequestState != 0)PushState(m_executionStack.top()->requestState());//Check if push state
		if (m_executionStack.top()->quitState())PopState();//Check if pop State
		if (m_executionStack.size() && m_executionStack.top()->forceState() != -1) {
			int WantedState = m_executionStack.top()->forceState();

			while (m_executionStack.size() && m_executionStack.top()->ID != WantedState) {
				m_executionStack.top()->quitState();
				PopState();
			}
		}
	}
	ExitGame();
}

void PixelArena::PopState()
{
	m_executionStack.top()->endState();
	delete m_executionStack.top();
	m_executionStack.pop();
}

void PixelArena::PushState(int _requestedState)
{
	switch (_requestedState) {
	case eGameplay:
		m_executionStack.push(new State_Gameplay(m_window, &Resources));
		break;
	case eMenu:
		m_executionStack.push(new State_Gameplay(m_window, &Resources));
		break;
	case ePause:
		m_executionStack.push(new State_Pause(m_window, &Resources));
		break;
	default:
		break;
	}
}

void PixelArena::ExitGame()
{
	//do stuff that i need before i close
	m_window->close();
}

void PixelArena::InitTextures()
{
	if (!m_screenBuffer.create(m_winWidth, m_winHeight)) {
		std::string Error = "Could not Create m_screenBuffer";
		InfoTool.ERR(5, Error);
	}
}


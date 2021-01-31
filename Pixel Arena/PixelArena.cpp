#include "PixelArena.h"

PixelArena::PixelArena()
{
	//Init default and get settings from settings file
	LoadSettings();

	//Create window
	this->m_window = new sf::RenderWindow(sf::VideoMode(m_winWidth, m_winHeight), m_winName, sf::Style::Titlebar | sf::Style::Close );
	m_window->setVerticalSyncEnabled(false);

	//Set Window Icon
	//Icon is copied no need for it to hang around
	sf::Image icon;
	icon.loadFromFile("Textures/GUI/Icon.png");;
	m_window->setIcon(icon.getSize().x,icon.getSize().y,icon.getPixelsPtr());

	//Set Window Cursor
	//Cursor is copied
	sf::Image im_cursor;
	im_cursor.loadFromFile("Textures/GUI/Cursor.png");;
	sf::Cursor Cursor;
	Cursor.loadFromPixels(im_cursor.getPixelsPtr(), sf::Vector2u(im_cursor.getSize().x, im_cursor.getSize().y), sf::Vector2u(0.0, 0.0));
	m_window->setMouseCursor(Cursor);

	//Init Screen Buffer mainly
	InitTextures();
}

PixelArena::~PixelArena()
{
	//Cleanup Window
	delete m_window;

	//Exit from Stack in order (saving data if need be)
	while (!m_executionStack.empty()) {
		delete m_executionStack.top();
		m_executionStack.pop();
	}
}

void PixelArena::Run()
{
	//m_executionStack.push(new State_Gameplay(m_window,&Resources));

	//Push MainMenu to stack execution stack
	m_executionStack.push(new State_MainMenu(m_window, &Resources));
	MainLoop();// Enter Main Loop
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
		std::getline(ifs, m_winName);//Get app name
		ifs >> m_winWidth >> m_winHeight;//Get Window Size
	}
	ifs.close();

}

void PixelArena::MainLoop()
{
	//Main App Loop
	while (m_window->isOpen() && !m_executionStack.empty()) {

		//if we resume a state that has been paused run some actions before resuming
		if (m_executionStack.top()->m_bResume)m_executionStack.top()->resumeState();

		m_executionStack.top()->eventLoop();//Resolve SFML events
		m_executionStack.top()->input(m_fTime);//Resolve Player Input
		m_executionStack.top()->update(m_fTime);//Update State
		m_executionStack.top()->draw(&m_screenBuffer);//Render State
		//Display
		m_window->draw(sf::Sprite(m_screenBuffer.getTexture()), &Resources.m_sFlipScreen);//Draw ScreenBuffer to Window
		m_window->display();//Display Window

		//Timing
		m_fTime = m_cClock.Count();//Get Frame Time

		//GameState Controller
		if (m_executionStack.top()->m_iRequestState != 0)PushState(m_executionStack.top()->requestState());//Check if push state
		if (m_executionStack.top()->quitState())PopState();//Check if pop State
		if (m_executionStack.size() && m_executionStack.top()->forceState() != -1) {//Force go to state that is lower in stack, pop unwanted
			int WantedState = m_executionStack.top()->forceState();

			while (m_executionStack.size() && m_executionStack.top()->ID != WantedState) {
				m_executionStack.top()->quitState();
				PopState();
			}
		}
	}
	ExitGame();//Exit App
}

void PixelArena::PopState()
{
	//Remove State from the top of the execution Stack
	m_executionStack.top()->endState();//Let state save its data/ perform actions before exiting
	delete m_executionStack.top();// Destruct state at the top of the stack
	m_executionStack.pop();// pop the state at the top from the stack
}

void PixelArena::PushState(int _requestedState)
{
	//Push State that is requested by another State
	switch (_requestedState) {
	case eGameplay:
		m_executionStack.push(new State_Gameplay(m_window, &Resources));
		break;
	case eMenu:
		m_executionStack.push(new State_MainMenu(m_window, &Resources));
		break;
	case eEditor:
		m_executionStack.push(new State_Editor(m_window, &Resources));
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
	m_window->close();//<Close Window
}

void PixelArena::InitTextures()
{
	//Create a ScreenBuffer the size of Window
	if (!m_screenBuffer.create(m_winWidth, m_winHeight)) {
		std::string Error = "Could not Create m_screenBuffer";
		InfoTool.ERR(5, Error);
	}
}


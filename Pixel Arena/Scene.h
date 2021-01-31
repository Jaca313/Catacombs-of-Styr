#pragma once
#include "Button.h"
#include "ResourceManager.h"
#include <map>
enum Scenes { ///< enum with ID of Scenes
	Main_Menu,
	Help,
	Options,
	Pause
};
class Scene ///< Is the Base Class for Scenes with interactable buttons and text
{
public:
	Scene();///< Default Constructor  (not used/class should not be constructed)
	virtual void drawScene(sf::RenderTarget& _target, sf::RenderStates _states = sf::RenderStates::Default); ///< Draws Scene (future proof for editing internals)
	void draw(sf::RenderTarget& _target, sf::RenderStates _states = sf::RenderStates::Default) const;///< Only Draws Scene

	void updateButtons(sf::Vector2f _mousePos);///< Checks Button States and Updates it
public://was protected
	std::map<std::string, Button> Buttons;///< Contains all buttons in a map
	std::map<std::string, sf::RectangleShape> Backgrounds;///< Contains all backgrounds in a map
protected:
	ResourceManager& Resources = ResourceManager::getInstance();///< Access to Resources
};


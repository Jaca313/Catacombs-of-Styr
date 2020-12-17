#pragma once
#include "Button.h"
#include "ResourceManager.h"
#include <map>
enum Scenes {
	Main_Menu,
	Help,
	Options,
	Pause
};
class Scene
{
public:
	Scene();
	virtual void drawScene(sf::RenderTarget& _target, sf::RenderStates _states = sf::RenderStates::Default);
	void draw(sf::RenderTarget& _target, sf::RenderStates _states = sf::RenderStates::Default) const;

	void updateButtons(sf::Vector2f _mousePos);
public://was protected
	std::map<std::string, Button> Buttons;
	std::map<std::string, sf::RectangleShape> Backgrounds;
protected:
	ResourceManager& Resources = ResourceManager::getInstance();

};


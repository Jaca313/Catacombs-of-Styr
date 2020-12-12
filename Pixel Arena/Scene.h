#pragma once
#include "Button.h"
#include "ResourceManager.h"
#include <map>
class Scene : public sf::Drawable
{
public:
	Scene();
	virtual void drawScene(sf::RenderTarget& _target, sf::RenderStates _states = sf::RenderStates::Default);
	void draw(sf::RenderTarget& _target, sf::RenderStates _states = sf::RenderStates::Default) const;
protected:
	std::map<std::string, Button> Buttons;
	std::map<std::string, sf::RectangleShape> Backgrounds;
	ResourceManager& Resources = ResourceManager::getInstance();
};


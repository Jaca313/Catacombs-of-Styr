#pragma once
#include "Scene.h"

class Scene_MainMenu : public Scene
{
public:
	Scene_MainMenu();
	void drawScene(sf::RenderTarget& _target, sf::RenderStates _states = sf::RenderStates::Default) override;

};


#pragma once
#include "Scene.h"

class Scene_MainMenu : public Scene///< Scene for Main Menu Screen
{
public:
	Scene_MainMenu();///< Constructs Buttons and Background
	void drawScene(sf::RenderTarget& _target, sf::RenderStates _states = sf::RenderStates::Default) override;///< Draws Scene (scales and updates Images, Buttons at the same time)

};


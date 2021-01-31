#pragma once
#include "Scene.h"
class Scene_Options : public Scene///< Scene for Options Screen
{
public:
	Scene_Options();///< Constructs Buttons and Background
	void drawScene(sf::RenderTarget& _target, sf::RenderStates _states = sf::RenderStates::Default) override;///< Draws Scene (scales and updates Images, Buttons at the same time)
};


#pragma once
#include "Scene.h"
class Scene_Pause : public Scene///< Scene for Pause Screen
{
public:
	Scene_Pause();///< Constructs Buttons and Background
	void drawScene(sf::RenderTarget& _target, sf::RenderStates _states = sf::RenderStates::Default) override;///< Draws Scene (scales and updates Images, Buttons at the same time)

};


#pragma once
#include "Scene.h"
class Scene_Help : public Scene ///< Scene for Help Screen
{
public:
	Scene_Help();///< Constructs Buttons and Background
	void drawScene(sf::RenderTarget& _target, sf::RenderStates _states = sf::RenderStates::Default) override;///< Draws Scene (scales and updates Images, Buttons at the same time)
};


#pragma once
#include "Scene.h"
class Scene_Options : public Scene
{
public:
	Scene_Options();
	void drawScene(sf::RenderTarget& _target, sf::RenderStates _states = sf::RenderStates::Default) override;
};


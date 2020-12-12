#pragma once
#include "Scene.h"
class Scene_Help : public Scene
{
public:
	Scene_Help();
	void drawScene(sf::RenderTarget& _target, sf::RenderStates _states = sf::RenderStates::Default) override;
};


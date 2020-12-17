#pragma once
#include "Scene.h"
class Scene_Pause : public Scene
{
public:
	Scene_Pause();
	void drawScene(sf::RenderTarget& _target, sf::RenderStates _states = sf::RenderStates::Default) override;

};


#include "stdafx.h"
#include "Scene.h"

Scene::Scene()
{
}

void Scene::drawScene(sf::RenderTarget& _target, sf::RenderStates _states)
{


	draw(_target, _states);
}

void Scene::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	for (auto Bg : Backgrounds) {
		_target.draw(Bg.second);
	}
	for (auto Btn : Backgrounds) {
		_target.draw(Btn.second);
	}
}

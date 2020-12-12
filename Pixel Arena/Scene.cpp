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
	for (auto& Bg : Backgrounds) {
		_target.draw(Bg.second, _states);
	}
	for (auto& Btn : Buttons) {
		//Btn.second.drawButton(_target, _states); //<- supposed to be this one
		_target.draw(Btn.second,_states);
	}
}

void Scene::updateButtons(sf::Vector2f _mousePos)
{
	for (auto &Btn : Buttons) {
		Btn.second.updateButton(_mousePos);
	}
}

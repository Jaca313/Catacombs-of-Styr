#include "stdafx.h"
#include "Scene_MainMenu.h"

Scene_MainMenu::Scene_MainMenu()
{
	sf::RectangleShape Logo;
	Backgrounds.insert(std::pair<std::string, sf::RectangleShape>("Logo", Logo));

	sf::RectangleShape Tablica;
	Backgrounds.insert(std::pair<std::string, sf::RectangleShape>("Tablica", Tablica));

}

void Scene_MainMenu::drawScene(sf::RenderTarget& _target, sf::RenderStates _states)
{
	float sizeX = _target.getSize().x;
	float sizeY = _target.getSize().y;

	//Big Rock Logo
	Backgrounds.at("Logo").setTexture(Resources.getTex(26));
	Backgrounds.at("Logo").setSize(sf::Vector2f(Backgrounds.at("Logo").getTexture()->getSize().x, Backgrounds.at("Logo").getTexture()->getSize().y));
	Backgrounds.at("Logo").setPosition(sizeX / 10.f, sizeY / 10.f);


	//Button Background
	Backgrounds.at("Tablica").setTexture(Resources.getTex(25));
	Backgrounds.at("Tablica").setSize(sf::Vector2f(Backgrounds.at("Tablica").getTexture()->getSize().x, Backgrounds.at("Tablica").getTexture()->getSize().y));
	Backgrounds.at("Tablica").setOrigin(Backgrounds.at("Tablica").getSize().x / 2, 0.f);
	Backgrounds.at("Tablica").setPosition(sizeX / 10.f + Backgrounds.at("Logo").getSize().x / 2, sizeY / 10.f + Backgrounds.at("Logo").getSize().y / 1.5f);

	draw(_target, _states);
}

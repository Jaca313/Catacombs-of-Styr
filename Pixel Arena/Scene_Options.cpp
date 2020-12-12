#include "stdafx.h"
#include "Scene_Options.h"

Scene_Options::Scene_Options()
{
	sf::RectangleShape Rocks;
	Backgrounds.insert(std::pair<std::string, sf::RectangleShape>("1_Rocks", Rocks));

	sf::RectangleShape Logo;
	Backgrounds.insert(std::pair<std::string, sf::RectangleShape>("2_Logo", Logo));

	sf::RectangleShape Tablica;
	Backgrounds.insert(std::pair<std::string, sf::RectangleShape>("3_Tablica", Tablica));

	Button Return(&Resources.m_sFontLanger, "Return", 30, Resources.getTex(21), Resources.getTex(22), Resources.getTex(23));
	Buttons.insert(std::pair<std::string, Button>("1_Return", Return));
}

void Scene_Options::drawScene(sf::RenderTarget& _target, sf::RenderStates _states)
{
	float sizeX = _target.getSize().x;
	float sizeY = _target.getSize().y;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Rock Background
	Backgrounds.at("1_Rocks").setTexture(Resources.getTex(18));
	Backgrounds.at("1_Rocks").setSize(sf::Vector2f(sizeX, sizeY));
	Backgrounds.at("1_Rocks").setPosition(0.f, 0.f);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Big Rock Logo
	Backgrounds.at("2_Logo").setTexture(Resources.getTex(26));
	Backgrounds.at("2_Logo").setSize(sf::Vector2f(Backgrounds.at("2_Logo").getTexture()->getSize().x, Backgrounds.at("2_Logo").getTexture()->getSize().y));
	Backgrounds.at("2_Logo").setOrigin(Backgrounds.at("2_Logo").getSize().x / 2.f, 0.f);
	Backgrounds.at("2_Logo").setPosition(sizeX / 2.f, 0.f);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Button Background
	Backgrounds.at("3_Tablica").setTexture(Resources.getTex(25));
	Backgrounds.at("3_Tablica").setSize(sf::Vector2f(Backgrounds.at("2_Logo").getTexture()->getSize().x, Backgrounds.at("3_Tablica").getTexture()->getSize().y));
	Backgrounds.at("3_Tablica").setOrigin(Backgrounds.at("3_Tablica").getSize().x / 2.f, 0.f);
	Backgrounds.at("3_Tablica").setPosition(Backgrounds.at("2_Logo").getPosition().x,Backgrounds.at("2_Logo").getSize().y / 1.5f);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Return Button
	Buttons.at("1_Return").m_sButton.setSize(sf::Vector2f(Backgrounds.at("1_Rocks").getSize().x / 1.5f / 3.f, Backgrounds.at("1_Rocks").getSize().y / 10.f));
	Buttons.at("1_Return").m_sButton.setOrigin(Buttons.at("1_Return").m_sButton.getSize().x / 2.f, 0.f);
	Buttons.at("1_Return").m_sButton.setPosition(sf::Vector2f(Backgrounds.at("1_Rocks").getPosition().x,
		Backgrounds.at("1_Rocks").getPosition().y + Backgrounds.at("1_Rocks").getSize().x / 3.5f + Buttons.at("1_Return").m_sButton.getSize().y * 5.f));

	Buttons.at("1_Return").m_ssText.setPosition(
		Buttons.at("1_Return").m_sButton.getPosition().x - Buttons.at("1_Return").m_ssText.getGlobalBounds().width / 2.f,
		Buttons.at("1_Return").m_sButton.getPosition().y + Buttons.at("1_Return").m_ssText.getGlobalBounds().height / 2.f
	);

	Buttons.at("1_Return").m_ssText.setFillColor(sf::Color(235, 183, 52, 200));
	Buttons.at("1_Return").m_ssText.setOutlineColor(sf::Color(0, 0, 0, 200));
	Buttons.at("1_Return").m_ssText.setOutlineThickness(1.5f);

	draw(_target, _states);
}

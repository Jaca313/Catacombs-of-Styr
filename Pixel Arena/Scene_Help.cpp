#include "stdafx.h"
#include "Scene_Help.h"

Scene_Help::Scene_Help()
{	
	sf::RectangleShape Logo;
	Backgrounds.insert(std::pair<std::string, sf::RectangleShape>("Logo", Logo));

	sf::RectangleShape Banner;
	Backgrounds.insert(std::pair<std::string, sf::RectangleShape>("Banner", Banner));



	Button Return(&Resources.m_sFontLanger, "Return", 30, Resources.getTex(21), Resources.getTex(22), Resources.getTex(23));
	Buttons.insert(std::pair<std::string, Button>("Return", Return));
}

void Scene_Help::drawScene(sf::RenderTarget& _target, sf::RenderStates _states)
{
	float sizeX = _target.getSize().x;
	float sizeY = _target.getSize().y;

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Big Rock Logo
	Backgrounds.at("Logo").setTexture(Resources.getTex(26));
	Backgrounds.at("Logo").setSize(sf::Vector2f(Backgrounds.at("Logo").getTexture()->getSize().x, Backgrounds.at("Logo").getTexture()->getSize().y));
	Backgrounds.at("Logo").setPosition(sizeX / 10.f, sizeY / 10.f);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Banner
	Backgrounds.at("Banner").setTexture(Resources.getTex(19));
	Backgrounds.at("Banner").setSize(sf::Vector2f(Backgrounds.at("Banner").getTexture()->getSize().x, Backgrounds.at("Banner").getTexture()->getSize().y));
	Backgrounds.at("Banner").setOrigin(Backgrounds.at("Banner").getSize().x / 2, 0.f);
	Backgrounds.at("Banner").setPosition(sizeX / 10.f + Backgrounds.at("Logo").getSize().x / 2 - 10, sizeY / 10.f + Backgrounds.at("Logo").getSize().y / 1.5f);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Return Button
	Buttons.at("Return").m_sButton.setSize(sf::Vector2f(Backgrounds.at("Banner").getSize().x / 1.5f / 3.f, Backgrounds.at("Banner").getSize().y / 10.f));
	Buttons.at("Return").m_sButton.setOrigin(Buttons.at("Return").m_sButton.getSize().x / 2.f, 0.f);
	Buttons.at("Return").m_sButton.setPosition(sf::Vector2f(Backgrounds.at("Banner").getPosition().x,
	Backgrounds.at("Banner").getPosition().y + Backgrounds.at("Banner").getSize().x / 3.5f + Buttons.at("Return").m_sButton.getSize().y * 5.f));

	Buttons.at("Return").m_ssText.setPosition(
		Buttons.at("Return").m_sButton.getPosition().x - Buttons.at("Return").m_ssText.getGlobalBounds().width / 2.f,
		Buttons.at("Return").m_sButton.getPosition().y + Buttons.at("Return").m_ssText.getGlobalBounds().height / 2.f
	);

	Buttons.at("Return").m_ssText.setFillColor(sf::Color(235, 183, 52, 200));
	Buttons.at("Return").m_ssText.setOutlineColor(sf::Color(0, 0, 0, 200));
	Buttons.at("Return").m_ssText.setOutlineThickness(1.5f);


	draw(_target, _states);
}

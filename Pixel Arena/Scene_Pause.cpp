#include "stdafx.h"
#include "Scene_Pause.h"

Scene_Pause::Scene_Pause()
{
	//Constructs Buttons and Backgrounds

	sf::RectangleShape Logo;
	Backgrounds.insert(std::pair<std::string, sf::RectangleShape>("Logo", Logo));

	sf::RectangleShape Tablica;
	Backgrounds.insert(std::pair<std::string, sf::RectangleShape>("Tablica", Tablica));

	Button Resume(&Resources.m_sFontLanger, "Resume", 25, Resources.getTex(20), Resources.getTex(22), Resources.getTex(23));
	Buttons.insert(std::pair<std::string, Button>("Resume", Resume));

	Button ExitMenu(&Resources.m_sFontLanger, "Exit to Menu", 25, Resources.getTex(21), Resources.getTex(22), Resources.getTex(23));
	Buttons.insert(std::pair<std::string, Button>("ExitMenu", ExitMenu));

	Button Quit(&Resources.m_sFontLanger, "Quit", 25, Resources.getTex(24), Resources.getTex(22), Resources.getTex(23));
	Buttons.insert(std::pair<std::string, Button>("Quit", Quit));
}

void Scene_Pause::drawScene(sf::RenderTarget& _target, sf::RenderStates _states)
{
	float sizeX = _target.getSize().x;
	float sizeY = _target.getSize().y;

	//Scaling Factors
	float XScale = (1920.f / sizeX);
	float YScale = (1920.f / sizeX);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Big Rock Logo
	Backgrounds.at("Logo").setTexture(Resources.getTex(26));
	Backgrounds.at("Logo").setSize(sf::Vector2f(Backgrounds.at("Logo").getTexture()->getSize().x * XScale, Backgrounds.at("Logo").getTexture()->getSize().y * YScale));
	Backgrounds.at("Logo").setOrigin(Backgrounds.at("Logo").getSize().x / 2, 0.f);
	Backgrounds.at("Logo").setPosition(sizeX / 2.f, sizeY / 10.f);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Button Background
	Backgrounds.at("Tablica").setTexture(Resources.getTex(25));
	Backgrounds.at("Tablica").setSize(sf::Vector2f(Backgrounds.at("Tablica").getTexture()->getSize().x * XScale, Backgrounds.at("Tablica").getTexture()->getSize().y * YScale / 1.5f));
	Backgrounds.at("Tablica").setOrigin(Backgrounds.at("Tablica").getSize().x / 2, 0.f);
	Backgrounds.at("Tablica").setPosition(Backgrounds.at("Logo").getPosition().x, Backgrounds.at("Logo").getPosition().y + Backgrounds.at("Logo").getSize().y / 1.5f);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Resume Button
	Buttons.at("Resume").m_sButton.setSize(sf::Vector2f(Backgrounds.at("Tablica").getSize().x / 1.5f * XScale, Backgrounds.at("Tablica").getSize().y / 6.5f * YScale));
	Buttons.at("Resume").m_sButton.setOrigin(Buttons.at("Resume").m_sButton.getSize().x / 2.f, 0.f);
	Buttons.at("Resume").m_sButton.setPosition(sf::Vector2f(Backgrounds.at("Tablica").getPosition().x,
		Backgrounds.at("Tablica").getPosition().y + Backgrounds.at("Tablica").getSize().x / 3.5f));

	Buttons.at("Resume").m_ssText.setPosition(
		Buttons.at("Resume").m_sButton.getPosition().x - Buttons.at("Resume").m_ssText.getGlobalBounds().width / 2.f,
		Buttons.at("Resume").m_sButton.getPosition().y + Buttons.at("Resume").m_ssText.getGlobalBounds().height / 2.f
	);

	Buttons.at("Resume").m_ssText.setFillColor(sf::Color(235, 183, 52, 200));
	Buttons.at("Resume").m_ssText.setOutlineColor(sf::Color(0, 0, 0, 200));
	Buttons.at("Resume").m_ssText.setOutlineThickness(1.5f);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//ExitMenu Button
	Buttons.at("ExitMenu").m_sButton.setSize(sf::Vector2f(Backgrounds.at("Tablica").getSize().x / 1.5f * XScale, Backgrounds.at("Tablica").getSize().y / 6.5f * YScale));
	Buttons.at("ExitMenu").m_sButton.setOrigin(Buttons.at("ExitMenu").m_sButton.getSize().x / 2.f, 0.f);
	Buttons.at("ExitMenu").m_sButton.setPosition(sf::Vector2f(Backgrounds.at("Tablica").getPosition().x,
		Backgrounds.at("Tablica").getPosition().y + Backgrounds.at("Tablica").getSize().x / 3.5f + Buttons.at("ExitMenu").m_sButton.getSize().y * 1.5f));

	Buttons.at("ExitMenu").m_ssText.setPosition(
		Buttons.at("ExitMenu").m_sButton.getPosition().x - Buttons.at("ExitMenu").m_ssText.getGlobalBounds().width / 2.f,
		Buttons.at("ExitMenu").m_sButton.getPosition().y + Buttons.at("ExitMenu").m_ssText.getGlobalBounds().height / 2.f
	);

	Buttons.at("ExitMenu").m_ssText.setFillColor(sf::Color(235, 183, 52, 200));
	Buttons.at("ExitMenu").m_ssText.setOutlineColor(sf::Color(0, 0, 0, 200));
	Buttons.at("ExitMenu").m_ssText.setOutlineThickness(1.5f);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Quit Button
	Buttons.at("Quit").m_sButton.setSize(sf::Vector2f(Backgrounds.at("Tablica").getSize().x / 1.5f * XScale, Backgrounds.at("Tablica").getSize().y / 6.5f * YScale));
	Buttons.at("Quit").m_sButton.setOrigin(Buttons.at("Quit").m_sButton.getSize().x / 2.f, 0.f);
	Buttons.at("Quit").m_sButton.setPosition(sf::Vector2f(Backgrounds.at("Tablica").getPosition().x,
		Backgrounds.at("Tablica").getPosition().y + Backgrounds.at("Tablica").getSize().x / 3.5f + Buttons.at("Quit").m_sButton.getSize().y * 3.f));

	Buttons.at("Quit").m_ssText.setPosition(
		Buttons.at("Quit").m_sButton.getPosition().x - Buttons.at("Quit").m_ssText.getGlobalBounds().width / 2.f,
		Buttons.at("Quit").m_sButton.getPosition().y + Buttons.at("Quit").m_ssText.getGlobalBounds().height / 2.f
	);

	Buttons.at("Quit").m_ssText.setFillColor(sf::Color(235, 183, 52, 200));
	Buttons.at("Quit").m_ssText.setOutlineColor(sf::Color(0, 0, 0, 200));
	Buttons.at("Quit").m_ssText.setOutlineThickness(1.5f);
	draw(_target, _states);
}

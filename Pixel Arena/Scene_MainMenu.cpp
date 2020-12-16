#include "stdafx.h"
#include "Scene_MainMenu.h"

Scene_MainMenu::Scene_MainMenu()
{
	sf::RectangleShape Logo;
	Backgrounds.insert(std::pair<std::string, sf::RectangleShape>("Logo", Logo));

	sf::RectangleShape Tablica;
	Backgrounds.insert(std::pair<std::string, sf::RectangleShape>("Tablica", Tablica));

	Button Start(&Resources.m_sFontLanger,"Enter Catacombs",25,Resources.getTex(20),Resources.getTex(22),Resources.getTex(23));
	Buttons.insert(std::pair<std::string, Button>("Start", Start));

	Button Editor(&Resources.m_sFontLanger, "Editor", 25, Resources.getTex(21), Resources.getTex(22), Resources.getTex(23));
	Buttons.insert(std::pair<std::string, Button>("Editor", Editor));

	Button Options(&Resources.m_sFontLanger, "Options", 25, Resources.getTex(21), Resources.getTex(22), Resources.getTex(23));
	Buttons.insert(std::pair<std::string, Button>("Options", Options));

	Button Controls(&Resources.m_sFontLanger, "Controls", 25, Resources.getTex(21), Resources.getTex(22), Resources.getTex(23));
	Buttons.insert(std::pair<std::string, Button>("Controls", Controls));

	Button Help(&Resources.m_sFontLanger, "Help", 25, Resources.getTex(21), Resources.getTex(22), Resources.getTex(23));
	Buttons.insert(std::pair<std::string, Button>("Help", Help));

	Button Quit(&Resources.m_sFontLanger, "Quit", 25, Resources.getTex(24), Resources.getTex(22), Resources.getTex(23));
	Buttons.insert(std::pair<std::string, Button>("Quit", Quit));

}

void Scene_MainMenu::drawScene(sf::RenderTarget& _target, sf::RenderStates _states)
{
	float sizeX = _target.getSize().x;
	float sizeY = _target.getSize().y;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Big Rock Logo
	Backgrounds.at("Logo").setTexture(Resources.getTex(26));
	Backgrounds.at("Logo").setSize(sf::Vector2f(Backgrounds.at("Logo").getTexture()->getSize().x, Backgrounds.at("Logo").getTexture()->getSize().y));
	Backgrounds.at("Logo").setPosition(sizeX / 10.f, sizeY / 10.f);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Button Background
	Backgrounds.at("Tablica").setTexture(Resources.getTex(25));
	Backgrounds.at("Tablica").setSize(sf::Vector2f(Backgrounds.at("Tablica").getTexture()->getSize().x, Backgrounds.at("Tablica").getTexture()->getSize().y));
	Backgrounds.at("Tablica").setOrigin(Backgrounds.at("Tablica").getSize().x / 2, 0.f);
	Backgrounds.at("Tablica").setPosition(sizeX / 10.f + Backgrounds.at("Logo").getSize().x / 2, sizeY / 10.f + Backgrounds.at("Logo").getSize().y / 1.5f);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Start Button
	Buttons.at("Start").m_sButton.setSize(sf::Vector2f(Backgrounds.at("Tablica").getSize().x / 1.5f, Backgrounds.at("Tablica").getSize().y / 10.f));
	Buttons.at("Start").m_sButton.setOrigin(Buttons.at("Start").m_sButton.getSize().x / 2.f, 0.f);
	Buttons.at("Start").m_sButton.setPosition(sf::Vector2f(Backgrounds.at("Tablica").getPosition().x,
														Backgrounds.at("Tablica").getPosition().y + Backgrounds.at("Tablica").getSize().x / 3.5f));

	Buttons.at("Start").m_ssText.setPosition(
		Buttons.at("Start").m_sButton.getPosition().x - Buttons.at("Start").m_ssText.getGlobalBounds().width / 2.f,
		Buttons.at("Start").m_sButton.getPosition().y + Buttons.at("Start").m_ssText.getGlobalBounds().height / 2.f
	);

	Buttons.at("Start").m_ssText.setFillColor(sf::Color(235, 183, 52, 200));
	Buttons.at("Start").m_ssText.setOutlineColor(sf::Color(0, 0, 0, 200));
	Buttons.at("Start").m_ssText.setOutlineThickness(1.5f);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Editor Button
	Buttons.at("Editor").m_sButton.setSize(sf::Vector2f(Backgrounds.at("Tablica").getSize().x / 1.5f, Backgrounds.at("Tablica").getSize().y / 10.f));
	Buttons.at("Editor").m_sButton.setOrigin(Buttons.at("Editor").m_sButton.getSize().x / 2.f, 0.f);
	Buttons.at("Editor").m_sButton.setPosition(sf::Vector2f(Backgrounds.at("Tablica").getPosition().x,
		Backgrounds.at("Tablica").getPosition().y + Backgrounds.at("Tablica").getSize().x / 3.5f + Buttons.at("Editor").m_sButton.getSize().y * 1.25f));

	Buttons.at("Editor").m_ssText.setPosition(
		Buttons.at("Editor").m_sButton.getPosition().x - Buttons.at("Editor").m_ssText.getGlobalBounds().width / 2.f,
		Buttons.at("Editor").m_sButton.getPosition().y + Buttons.at("Editor").m_ssText.getGlobalBounds().height / 2.f
	);

	Buttons.at("Editor").m_ssText.setFillColor(sf::Color(235, 183, 52, 200));
	Buttons.at("Editor").m_ssText.setOutlineColor(sf::Color(0, 0, 0, 200));
	Buttons.at("Editor").m_ssText.setOutlineThickness(1.5f);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Options Button
	Buttons.at("Options").m_sButton.setSize(sf::Vector2f(Backgrounds.at("Tablica").getSize().x / 1.5f, Backgrounds.at("Tablica").getSize().y / 10.f));
	Buttons.at("Options").m_sButton.setOrigin(Buttons.at("Options").m_sButton.getSize().x / 2.f, 0.f);
	Buttons.at("Options").m_sButton.setPosition(sf::Vector2f(Backgrounds.at("Tablica").getPosition().x,
		Backgrounds.at("Tablica").getPosition().y + Backgrounds.at("Tablica").getSize().x / 3.5f + Buttons.at("Options").m_sButton.getSize().y * 2.5f));

	Buttons.at("Options").m_ssText.setPosition(
		Buttons.at("Options").m_sButton.getPosition().x - Buttons.at("Options").m_ssText.getGlobalBounds().width / 2.f,
		Buttons.at("Options").m_sButton.getPosition().y + Buttons.at("Options").m_ssText.getGlobalBounds().height / 2.f
	);

	Buttons.at("Options").m_ssText.setFillColor(sf::Color(235, 183, 52, 200));
	Buttons.at("Options").m_ssText.setOutlineColor(sf::Color(0, 0, 0, 200));
	Buttons.at("Options").m_ssText.setOutlineThickness(1.5f);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Controls Button
	Buttons.at("Controls").m_sButton.setSize(sf::Vector2f(Backgrounds.at("Tablica").getSize().x / 1.5f, Backgrounds.at("Tablica").getSize().y / 10.f));
	Buttons.at("Controls").m_sButton.setOrigin(Buttons.at("Controls").m_sButton.getSize().x / 2.f, 0.f);
	Buttons.at("Controls").m_sButton.setPosition(sf::Vector2f(Backgrounds.at("Tablica").getPosition().x,
		Backgrounds.at("Tablica").getPosition().y + Backgrounds.at("Tablica").getSize().x / 3.5f + Buttons.at("Controls").m_sButton.getSize().y * 3.75f));

	Buttons.at("Controls").m_ssText.setPosition(
		Buttons.at("Controls").m_sButton.getPosition().x - Buttons.at("Controls").m_ssText.getGlobalBounds().width / 2.f,
		Buttons.at("Controls").m_sButton.getPosition().y + Buttons.at("Controls").m_ssText.getGlobalBounds().height / 2.f
	);

	Buttons.at("Controls").m_ssText.setFillColor(sf::Color(235, 183, 52, 200));
	Buttons.at("Controls").m_ssText.setOutlineColor(sf::Color(0, 0, 0, 200));
	Buttons.at("Controls").m_ssText.setOutlineThickness(1.5f);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Help Button
	Buttons.at("Help").m_sButton.setSize(sf::Vector2f(Backgrounds.at("Tablica").getSize().x / 1.5f, Backgrounds.at("Tablica").getSize().y / 10.f));
	Buttons.at("Help").m_sButton.setOrigin(Buttons.at("Help").m_sButton.getSize().x / 2.f, 0.f);
	Buttons.at("Help").m_sButton.setPosition(sf::Vector2f(Backgrounds.at("Tablica").getPosition().x,
		Backgrounds.at("Tablica").getPosition().y + Backgrounds.at("Tablica").getSize().x / 3.5f + Buttons.at("Help").m_sButton.getSize().y * 5.f));

	Buttons.at("Help").m_ssText.setPosition(
		Buttons.at("Help").m_sButton.getPosition().x - Buttons.at("Help").m_ssText.getGlobalBounds().width / 2.f,
		Buttons.at("Help").m_sButton.getPosition().y + Buttons.at("Help").m_ssText.getGlobalBounds().height / 2.f
	);

	Buttons.at("Help").m_ssText.setFillColor(sf::Color(235, 183, 52, 200));
	Buttons.at("Help").m_ssText.setOutlineColor(sf::Color(0, 0, 0, 200));
	Buttons.at("Help").m_ssText.setOutlineThickness(1.5f);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Quit Button
	Buttons.at("Quit").m_sButton.setSize(sf::Vector2f(Backgrounds.at("Tablica").getSize().x / 1.5f, Backgrounds.at("Tablica").getSize().y / 10.f));
	Buttons.at("Quit").m_sButton.setOrigin(Buttons.at("Quit").m_sButton.getSize().x / 2.f, 0.f);
	Buttons.at("Quit").m_sButton.setPosition(sf::Vector2f(Backgrounds.at("Tablica").getPosition().x,
		Backgrounds.at("Tablica").getPosition().y + Backgrounds.at("Tablica").getSize().x / 3.5f + Buttons.at("Quit").m_sButton.getSize().y * 6.25f));

	Buttons.at("Quit").m_ssText.setPosition(
		Buttons.at("Quit").m_sButton.getPosition().x - Buttons.at("Quit").m_ssText.getGlobalBounds().width / 2.f,
		Buttons.at("Quit").m_sButton.getPosition().y + Buttons.at("Quit").m_ssText.getGlobalBounds().height / 2.f
	);

	Buttons.at("Quit").m_ssText.setFillColor(sf::Color(235, 183, 52, 200));
	Buttons.at("Quit").m_ssText.setOutlineColor(sf::Color(0, 0, 0, 200));
	Buttons.at("Quit").m_ssText.setOutlineThickness(1.5f);


	draw(_target, _states);
}

#include "stdafx.h"
#include "InGameUI.h"


InGameUI::InGameUI()
{
	InitialSetup(10);
}

void InGameUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->Background, states);
	target.draw(this->Portrait, states);
	target.draw(this->HealthBarBackground, states);
	target.draw(this->HealthBar, states);
}

void InGameUI::drawUI(Player* Butcher,sf::RenderTarget& target, sf::RenderStates states)
{
	this->sizeX = target.getSize().x / 3.0;
	this->sizeY = target.getSize().y / 5.0;

	this->PositionX = sizeX;
	this->PositionY = target.getSize().y - sizeY;

	UpdateUIScale(Butcher);

	draw(target, states);
}

void InGameUI::UpdateUIScale(Player* Butcher)
{

	Background.setPosition(PositionX, PositionY);
	Background.setSize(sf::Vector2f(sizeX, sizeY));

	float Health = Butcher->getHealth() / 100.0;//read this from player
	HealthBar.setPosition(PositionX + sizeX / 3.0, PositionY + 9 * sizeY / 10.0);
	HealthBar.setSize(sf::Vector2f(Health * sizeX / 3.0, sizeY * 0.1));
	int HealthFace = 7.0 - Health * 7.0;

	Portrait.setOrigin(sf::Vector2f(Portrait.getSize().x / 2.0, 0.0));
	Portrait.setPosition(PositionX + sizeX/2.0, PositionY + sizeY/10.0);
	float PortraitYtoXScale = (float)Portrait.getTexture()->getSize().y / (float)Portrait.getTexture()->getSize().x * 7.0;
	float PortraitUIScale = 0.25 * sizeX;
	Portrait.setTextureRect(sf::IntRect(sf::Vector2i(HealthFace* Portrait.getTexture()->getSize().x / 7.0+1.0,1.0), sf::Vector2i(Portrait.getTexture()->getSize().x/7.0-1.0, Portrait.getTexture()->getSize().y - 1.0)));
	Portrait.setSize(sf::Vector2f(PortraitUIScale, PortraitUIScale * PortraitYtoXScale));

	HealthBarBackground.setPosition(PositionX + sizeX / 3.0, PositionY + 9 * sizeY / 10.0);
	HealthBarBackground.setSize(sf::Vector2f(sizeX/3.0, sizeY * 0.1));



	
}

void InGameUI::InitialSetup(int Face)
{
	Background.setFillColor(sf::Color::Cyan);
	Background.setOutlineColor(sf::Color::Black);
	Background.setOutlineThickness(10.f);

	Face = Face > 14 ? 14 : Face;
	Face = Face < 10 ? 10 : Face;
	Portrait.setTexture(Resources.getTex(Face));

	HealthBarBackground.setFillColor(sf::Color(120, 120, 120, 120));
	HealthBarBackground.setOutlineColor(sf::Color(194, 194, 194, 255));
	HealthBarBackground.setOutlineThickness(10.f);
	HealthBar.setFillColor(sf::Color::Red);

}

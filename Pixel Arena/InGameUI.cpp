#include "stdafx.h"
#include "InGameUI.h"


InGameUI::InGameUI()
{
	//@param Init Face to be used as character portrait
	//Initializes HUD Elements
	InitialSetup(10);
}

void InGameUI::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	//drawing of UI elements
	_target.draw(this->m_sBackground, _states);
	_target.draw(this->m_sPortrait, _states);
	_target.draw(this->m_sHealthBarBackground, _states);
	_target.draw(this->m_sHealthBar, _states);
}

void InGameUI::drawUI(Player* _Butcher,sf::RenderTarget& _target, sf::RenderStates _states)
{
	//Gets size of target for proper scaling
	this->SizeX = _target.getSize().x / 3.f;
	this->SizeY = _target.getSize().y / 5.f;

	//Set HUD Position
	this->PositionX = SizeX;
	this->PositionY = _target.getSize().y - SizeY;

	//updates scaling and position (@param Player Health)
	UpdateUIScale(_Butcher);

	//draws elements of HUD
	draw(_target, _states);
}

void InGameUI::UpdateUIScale(Player* _Butcher)
{
	//Background
	m_sBackground.setPosition(PositionX, PositionY);
	m_sBackground.setSize(sf::Vector2f(SizeX, SizeY));

	//Health Bar and Health dependent Portrait
	float Health = _Butcher->getHealth() / 100.f;//read this from player
	m_sHealthBar.setPosition(PositionX + SizeX / 3.f, PositionY + 9 * SizeY / 10.f);
	m_sHealthBar.setSize(sf::Vector2f(Health * SizeX / 3.f, SizeY * 0.1f));
	m_sHealthBarBackground.setPosition(PositionX + SizeX / 3.f, PositionY + 9 * SizeY / 10.f);
	m_sHealthBarBackground.setSize(sf::Vector2f(SizeX / 3.f, SizeY * 0.1f));

	//Get Face from SpriteSheet
	int HealthFace = int(6.99f - Health * 7.f);

	m_sPortrait.setOrigin(sf::Vector2f(m_sPortrait.getSize().x / 2.f, 0.f));
	m_sPortrait.setPosition(PositionX + SizeX/2.f, PositionY + SizeY/10.f);
	float PortraitYtoXScale = (float)m_sPortrait.getTexture()->getSize().y / (float)m_sPortrait.getTexture()->getSize().x * 7.f;
	float PortraitUIScale = 0.25f * SizeX;
	m_sPortrait.setTextureRect(sf::IntRect(sf::Vector2i(HealthFace* m_sPortrait.getTexture()->getSize().x / 7.f+1.f,1.f), sf::Vector2i(m_sPortrait.getTexture()->getSize().x/7.f-1.f, m_sPortrait.getTexture()->getSize().y - 1.f)));
	m_sPortrait.setSize(sf::Vector2f(PortraitUIScale, PortraitUIScale * PortraitYtoXScale));

}

void InGameUI::InitialSetup(int _Face)
{
	//m_sBackground.setFillColor(sf::Color::Cyan);
	//m_sBackground.setOutlineColor(sf::Color::Black);
	//m_sBackground.setOutlineThickness(10.f);
	
	//Set Background Texture of HUD
	m_sBackground.setTexture(Resources.getTex(28));

	//Legacy code (makes sure that the face is one of the available)
	_Face = _Face > 10 ? 10 : _Face;
	_Face = _Face < 10 ? 10 : _Face;
	m_sPortrait.setTexture(Resources.getTex(_Face));

	//Sets Healthbar
	m_sHealthBarBackground.setFillColor(sf::Color(120, 120, 120, 255));
	m_sHealthBarBackground.setOutlineColor(sf::Color(194, 194, 194, 255));
	m_sHealthBarBackground.setOutlineThickness(10.f);
	m_sHealthBarBackground.setTexture(Resources.getTex(27));
	//m_sHealthBar.setFillColor(sf::Color::Red);
	m_sHealthBar.setTexture(Resources.getTex(27));

}

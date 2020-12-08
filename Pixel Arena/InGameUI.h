#pragma once
#include "ResourceManager.h"
#include "Player.h"
class InGameUI : public sf::Drawable
{
public:
	InGameUI();
private:
	//Screen Properties
	float SizeX  = 0.f;///< Property of Screen
	float SizeY = 0.f;///< Property of Screen

	float PositionX = 0.f;///< Property of Screen
	float PositionY = 0.f;///< Property of Screen

	//Resources
	ResourceManager& Resources = ResourceManager::getInstance();///<Access to Resource Manager

	//UI Elements
	sf::RectangleShape m_sBackground;///< Box in mid-bottom for background UI
	sf::RectangleShape m_sPortrait;///< Portrait of Character

	sf::RectangleShape m_sHealthBarBackground;///< Backing element for healthbard
	sf::RectangleShape m_sHealthBar;///< Healthbar for player

public:
	void drawUI(Player* _Butcher, sf::RenderTarget& _target, sf::RenderStates _states = sf::RenderStates::Default);///< interface for updating UI and drawing
private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states = sf::RenderStates::Default) const  override;///< does only drawing
	
	void UpdateUIScale(Player* _Butcher);///< updates scaling position of UI elements

	void InitialSetup(int _Face);///< Sets up nonchanging properties of UI elements
};


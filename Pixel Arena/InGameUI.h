#pragma once
#include "ResourceManager.h"
#include "Player.h"
class InGameUI : public sf::Drawable
{
public:
	InGameUI();
private:
	//Screen Properties
	float sizeX  = 0.f;///< Property of Screen
	float sizeY = 0.f;///< Property of Screen

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
	void drawUI(Player* Butcher, sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);///< interface for updating UI and drawing
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const  override;///< does only drawing
	
	void UpdateUIScale(Player* Butcher);///< updates scaling position of UI elements

	void InitialSetup(int Face);///< Sets up nonchanging properties of UI elements
};


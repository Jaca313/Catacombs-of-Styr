#pragma once
#include "ResourceManager.h"
#include "Player.h"
class InGameUI : public sf::Drawable
{
public:
	InGameUI();
private:
	float sizeX  = 0.f;
	float sizeY = 0.f;

	float PositionX = 0.f;
	float PositionY = 0.f;

	ResourceManager& Resources = ResourceManager::getInstance();

	sf::RectangleShape Background;
	sf::RectangleShape Portrait;

	sf::RectangleShape HealthBarBackground;
	sf::RectangleShape HealthBar;

public:
	void drawUI(Player* Butcher, sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const  override;
	
	void UpdateUIScale(Player* Butcher);

	void InitialSetup(int Face);
};


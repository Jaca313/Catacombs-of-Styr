#pragma once
#include "ResourceManager.h"
class InGameUI : public sf::Drawable
{
public:
	InGameUI(int Face);
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
	void drawUI(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const  override;
	
	void UpdateUIScale();

	void InitialSetup(int Face);
};


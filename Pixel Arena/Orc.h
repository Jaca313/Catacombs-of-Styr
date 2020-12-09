#pragma once
#include "Entity.h"
class Orc : public sf::Drawable, public Entity
{
public:
	Orc(sf::Vector2f pos,int Texture);
private:
	sf::RectangleShape Object;
public:
	void drawEntity(float* Z_Buffer,sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const  override;

	int AnimSizeX;//on construction
	int AnimSizeY;
	void UpdateAnimation(sf::RenderTarget& target, float* Z_Buffer);
};


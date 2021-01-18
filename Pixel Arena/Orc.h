#pragma once
#include "Entity.h"
class Orc : public sf::Drawable, public Entity
{
public:
	Orc(sf::Vector2f pos,int Texture);
private:
	sf::RectangleShape Object;///< Sprite
public:
	void drawEntity(float* Z_Buffer,sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const  override;

	int AnimSizeX;///< on construction Size of SpriteSheet
	int AnimSizeY;///< on construction Size of SpriteSheet
	void UpdateAnimation(sf::RenderTarget& target, float* Z_Buffer);
};


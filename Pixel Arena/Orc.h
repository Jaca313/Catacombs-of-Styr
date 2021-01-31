#pragma once
#include "Entity.h"
class Orc : public sf::Drawable, public Entity ///< Basic Enemy Orc Class
{
public:
	Orc(sf::Vector2f pos,int Texture);///< Constructor with position and texture of enemy
private:
	sf::RectangleShape Object;///< Sprite
public:
	void drawEntity(float* Z_Buffer,sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);///< Draws and Updates Entity anim

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const  override;///< Draws Entity

	int AnimSizeX;///< on construction Size of SpriteSheet
	int AnimSizeY;///< on construction Size of SpriteSheet
	void UpdateAnimation(sf::RenderTarget& target, float* Z_Buffer);///< Updates Sprites
};


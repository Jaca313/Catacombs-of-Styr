#pragma once
#include "SFML/Graphics.hpp"

class Button : public sf::Drawable
{
public:
	Button(sf::Vector2f _pos, sf::Vector2f _size,
		sf::Font* _font, std::string _text,
		sf::Color _idleCol, sf::Color _hoverCol, sf::Color _activeCol);
	~Button();
private:
	sf::RectangleShape m_sButton;
	sf::Font* m_sFont;
	sf::Text m_ssText;

	sf::Color m_sIdleColor;
	sf::Color m_sHoverColor;
	sf::Color m_sActiveColor;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const  override;
public:
	void updateButton(sf::Vector2f _mousePos);
	void drawButton(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);

};

 
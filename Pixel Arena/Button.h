#pragma once
#include "SFML/Graphics.hpp"

class Button
{
public:
	Button(sf::Vector2f _pos, sf::Vector2f _size,
		sf::Font* _font, std::string text,
		sf::Color _idleCol, sf::Color _hoverCol, sf::Color _activeCol);
	~Button();
private:
	sf::RectangleShape m_sShape;
	sf::Font* m_sFont;
	sf::Text m_stext;

	sf::Color m_sIdleColor;
	sf::Color m_sHoverColor;
	sf::Color m_sActiveColor;


};

 
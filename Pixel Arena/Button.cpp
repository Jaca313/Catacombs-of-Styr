#include "stdafx.h"
#include "Button.h"

Button::Button(sf::Vector2f _pos, sf::Vector2f _size,
	sf::Font* _font, std::string _text,
	sf::Color _idleCol, sf::Color _hoverCol, sf::Color _activeCol)
{
	m_sButton.setPosition(_pos);
	m_sButton.setSize(_size);

	m_sFont = _font;
	m_ssText.setFont(*m_sFont);
	m_ssText.setString(_text);
	m_ssText.setFillColor(sf::Color::Red);
	m_ssText.setOutlineColor(sf::Color::White);
	m_ssText.setPosition(
		m_sButton.getPosition().x / 2.f - m_ssText.getGlobalBounds().width / 2.f,
		m_sButton.getPosition().y / 2.f - m_ssText.getGlobalBounds().height / 2.f
	);

	m_sIdleColor = _idleCol;
	m_sHoverColor = _idleCol;
	m_sActiveColor = _activeCol;

	

}

Button::~Button()
{
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sButton);
	target.draw(m_ssText);
}

void Button::updateButton(sf::Vector2f _mousePos)
{
}

void Button::drawButton(sf::RenderTarget& target, sf::RenderStates states)
{
	draw(target, states);
}

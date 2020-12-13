#include "stdafx.h"
#include "Button.h"

Button::Button(sf::Vector2f _pos, sf::Vector2f _size, int _charSize,
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

	m_ssText.setCharacterSize(_charSize);
}

Button::Button(sf::Vector2f _pos, sf::Vector2f _size, int _charSize,
	sf::Font* _font, std::string _text,
	sf::Texture* _idleTex, sf::Texture* _hoverTex, sf::Texture* _activeTex)
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

	m_sIdleTex = _idleTex;
	m_sHoverTex = _hoverTex;
	m_sActiveTex = _activeTex;

	m_sButton.setTexture(m_sIdleTex);

	m_ssText.setCharacterSize(_charSize);
}

Button::Button(sf::Font* _font, std::string _text,int _charSize,
	sf::Texture* _idleTex, sf::Texture* _hoverTex, sf::Texture* _activeTex)
{
	m_sFont = _font;
	m_ssText.setFont(*m_sFont);
	m_ssText.setString(_text);
	m_ssText.setFillColor(sf::Color::Red);
	m_ssText.setOutlineColor(sf::Color::White);

	m_sIdleTex = _idleTex;
	m_sHoverTex = _hoverTex;
	m_sActiveTex = _activeTex;

	m_sButton.setTexture(m_sIdleTex);

	m_ssText.setCharacterSize(_charSize);
}

Button::Button(sf::Font* _font, std::string _text, int _charSize, sf::Color _idleCol, sf::Color _hoverCol, sf::Color _activeCol)
{
	m_sFont = _font;
	m_ssText.setFont(*m_sFont);
	m_ssText.setString(_text);
	m_ssText.setFillColor(sf::Color::Red);
	m_ssText.setOutlineColor(sf::Color::White);

	m_sIdleColor = _idleCol;
	m_sHoverColor = _hoverCol;
	m_sActiveColor = _activeCol;

	m_sButton.setFillColor(m_sIdleColor);

	m_ssText.setCharacterSize(_charSize);
}



Button::~Button()
{
}

void Button::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_states.texture = m_sButton.getTexture();
	_target.draw(m_sButton,_states);
	_target.draw(m_ssText,_states);
}

void Button::updateButton(sf::Vector2f _mousePos)
{

	if (m_sButton.getGlobalBounds().contains(_mousePos)) {
		m_sButton.setTexture(m_sHoverTex);
		m_sButton.setFillColor(m_sHoverColor);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			m_sButton.setTexture(m_sActiveTex);
			m_sButton.setFillColor(m_sActiveColor);
			m_bPressed = true;
			m_bReleased = false;
		}
		else if (m_bPressed) {
			m_bPressed = false;
			m_bReleased = true;
		}
	}
	else {
		m_sButton.setTexture(m_sIdleTex);
		m_sButton.setFillColor(m_sIdleColor);
		m_bPressed = false;
		m_bReleased = false;
	}
}

void Button::drawButton(sf::RenderTarget& target, sf::RenderStates states)
{
	//is not used!!!!
	draw(target, states);
}

bool Button::isPressed()
{
	bool returnValue = m_bPressed;
	m_bPressed = false;
	return returnValue;
}

bool Button::isReleased()
{
	bool returnValue = m_bReleased;
	m_bReleased = false;
	return returnValue;
}

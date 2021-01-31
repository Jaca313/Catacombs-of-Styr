#include "stdafx.h"
#include "Button.h"

Button::Button(sf::Vector2f _pos, sf::Vector2f _size, int _charSize,
	sf::Font* _font, std::string _text,
	sf::Color _idleCol, sf::Color _hoverCol, sf::Color _activeCol)
{
	//Set Size and Position
	m_sButton.setPosition(_pos);
	m_sButton.setSize(_size);

	//Setup Text with font, color, size, pos (in the middle of Button)
	m_sFont = _font;
	m_ssText.setFont(*m_sFont);
	m_ssText.setString(_text);
	m_ssText.setFillColor(sf::Color::Red);
	m_ssText.setOutlineColor(sf::Color::White);
	m_ssText.setPosition(
		m_sButton.getPosition().x / 2.f - m_ssText.getGlobalBounds().width / 2.f,
		m_sButton.getPosition().y / 2.f - m_ssText.getGlobalBounds().height / 2.f
	);
	
	//Assign Colors
	m_sIdleColor = _idleCol;
	m_sHoverColor = _idleCol;
	m_sActiveColor = _activeCol;

	//Set Font Size
	m_ssText.setCharacterSize(_charSize);
}

Button::Button(sf::Vector2f _pos, sf::Vector2f _size, int _charSize,
	sf::Font* _font, std::string _text,
	sf::Texture* _idleTex, sf::Texture* _hoverTex, sf::Texture* _activeTex)
{
	//Set Size and Position
	m_sButton.setPosition(_pos);
	m_sButton.setSize(_size);

	//Setup Text with font, color, size, pos (in the middle of Button)
	m_sFont = _font;
	m_ssText.setFont(*m_sFont);
	m_ssText.setString(_text);
	m_ssText.setFillColor(sf::Color::Red);
	m_ssText.setOutlineColor(sf::Color::White);
	m_ssText.setPosition(
		m_sButton.getPosition().x / 2.f - m_ssText.getGlobalBounds().width / 2.f,
		m_sButton.getPosition().y / 2.f - m_ssText.getGlobalBounds().height / 2.f
	);

	//Assign Textures
	m_sIdleTex = _idleTex;
	m_sHoverTex = _hoverTex;
	m_sActiveTex = _activeTex;

	m_sButton.setTexture(m_sIdleTex);

	//Set Font Size
	m_ssText.setCharacterSize(_charSize);
}

Button::Button(sf::Font* _font, std::string _text,int _charSize,
	sf::Texture* _idleTex, sf::Texture* _hoverTex, sf::Texture* _activeTex)
{
	//Setup Text with font, color
	m_sFont = _font;
	m_ssText.setFont(*m_sFont);
	m_ssText.setString(_text);
	m_ssText.setFillColor(sf::Color::Red);
	m_ssText.setOutlineColor(sf::Color::White);

	//Assign Textures
	m_sIdleTex = _idleTex;
	m_sHoverTex = _hoverTex;
	m_sActiveTex = _activeTex;

	m_sButton.setTexture(m_sIdleTex);

	//Set Font Size
	m_ssText.setCharacterSize(_charSize);
}

Button::Button(sf::Font* _font, std::string _text, int _charSize, sf::Color _idleCol, sf::Color _hoverCol, sf::Color _activeCol)
{
	//Setup Text with font, color
	m_sFont = _font;
	m_ssText.setFont(*m_sFont);
	m_ssText.setString(_text);
	m_ssText.setFillColor(sf::Color::Red);
	m_ssText.setOutlineColor(sf::Color::White);

	//Assign Colors
	m_sIdleColor = _idleCol;
	m_sHoverColor = _hoverCol;
	m_sActiveColor = _activeCol;

	m_sButton.setFillColor(m_sIdleColor);

	//Set Font Size
	m_ssText.setCharacterSize(_charSize);
}



Button::~Button()
{
}

void Button::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	//Draws Button with Color/Texture and Text(if any)
	_states.texture = m_sButton.getTexture();
	_target.draw(m_sButton,_states);
	_target.draw(m_ssText,_states);
}

void Button::updateButton(sf::Vector2f _mousePos)
{
	//Get Button State

	//If Contains
	if (m_sButton.getGlobalBounds().contains(_mousePos)) {
		m_sButton.setTexture(m_sHoverTex);
		m_sButton.setFillColor(m_sHoverColor);

		//If mouse left pressed and not released
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			m_sButton.setTexture(m_sActiveTex);
			m_sButton.setFillColor(m_sActiveColor);
			m_bPressed = true;
			m_bReleased = false;
		}
		else if (m_bPressed) {// if not mouse left pressed and inside (didnt exit from button meanwhile) (released button)
			m_bPressed = false;
			m_bReleased = true;
		}
	}
	else { // if mouse outside the button
		m_sButton.setTexture(m_sIdleTex);
		m_sButton.setFillColor(m_sIdleColor);
		m_bPressed = false;
		m_bReleased = false;
	}
}

void Button::drawButton(sf::RenderTarget& target, sf::RenderStates states)
{
	//is not used / for editing purposes if necessary in future
	draw(target, states);
}

bool Button::isPressed()
{
	// Returns Current Pressed state and zeroes it
	bool returnValue = m_bPressed;
	m_bPressed = false;
	return returnValue;
}

bool Button::isReleased()
{
	// Returns Current Released state and zeroes it
	bool returnValue = m_bReleased;
	m_bReleased = false;
	return returnValue;
}

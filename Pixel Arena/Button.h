#pragma once
#include "SFML/Graphics.hpp"

class Button : public sf::Drawable
{
public:
	Button(sf::Font* _font, std::string _text, int _charSize,
		sf::Texture* _idleTex, sf::Texture* _hoverTex, sf::Texture* _activeTex);

	Button(sf::Font* _font, std::string _text, int _charSize,
		sf::Color _idleCol, sf::Color _hoverCol, sf::Color _activeCol);

	Button(sf::Vector2f _pos, sf::Vector2f _size, int _charSize,
		sf::Font* _font, std::string _text,
		sf::Texture* _idleTex, sf::Texture* _hoverTex, sf::Texture* _activeTex);

	Button(sf::Vector2f _pos, sf::Vector2f _size, int _charSize,
		sf::Font* _font, std::string _text,
		sf::Color _idleCol, sf::Color _hoverCol, sf::Color _activeCol);
	~Button();
public:
	sf::RectangleShape m_sButton;
	sf::Text m_ssText;
private:


	sf::Font* m_sFont = nullptr;

	sf::Color m_sIdleColor = sf::Color::White;
	sf::Color m_sHoverColor = sf::Color::White;
	sf::Color m_sActiveColor = sf::Color::White;

	sf::Texture* m_sIdleTex = nullptr;
	sf::Texture* m_sHoverTex = nullptr;
	sf::Texture* m_sActiveTex = nullptr;


private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const  override;
public:
	void updateButton(sf::Vector2f _mousePos);
	void drawButton(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);///< is not used depreceated

private:
	bool m_bPressed = false;
	bool m_bReleased = false;

public:
	bool isPressed();
	bool isReleased();

};

 
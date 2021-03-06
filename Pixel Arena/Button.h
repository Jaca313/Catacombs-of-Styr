#pragma once
#include "SFML/Graphics.hpp"

class Button : public sf::Drawable ///< Interactive Button
{
public:
	//Various Constructors depending on needs
	Button(sf::Font* _font, std::string _text, int _charSize,
		sf::Texture* _idleTex, sf::Texture* _hoverTex, sf::Texture* _activeTex);///<Constructor with only Textures(no position and size)

	Button(sf::Font* _font, std::string _text, int _charSize,
		sf::Color _idleCol, sf::Color _hoverCol, sf::Color _activeCol);///<Constructor with only Colors(no position and size)

	Button(sf::Vector2f _pos, sf::Vector2f _size, int _charSize,
		sf::Font* _font, std::string _text,
		sf::Texture* _idleTex, sf::Texture* _hoverTex, sf::Texture* _activeTex);///<Constructor with only Textures

	Button(sf::Vector2f _pos, sf::Vector2f _size, int _charSize,
		sf::Font* _font, std::string _text,
		sf::Color _idleCol, sf::Color _hoverCol, sf::Color _activeCol);///<Constructor with only Colors
	~Button();///< Destructor (empty)
public:
	sf::RectangleShape m_sButton;///< Button Background
	sf::Text m_ssText;///< Button Text
private:


	sf::Font* m_sFont = nullptr;///< Button Text Font

	sf::Color m_sIdleColor = sf::Color::White;///< Button Color on Idle
	sf::Color m_sHoverColor = sf::Color::White;///< Button Color on Hover
	sf::Color m_sActiveColor = sf::Color::White;///< Button Color upon Press

	sf::Texture* m_sIdleTex = nullptr;///< Button Tex on Idle
	sf::Texture* m_sHoverTex = nullptr;///< Button Tex on Hover
	sf::Texture* m_sActiveTex = nullptr;///< Button Tex upon Press


private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const  override;///< Draws Button with Text
public:
	void updateButton(sf::Vector2f _mousePos);///< Updates Internal Button state (Texture and bools depending state(hover ,press,not active etc.)
	void drawButton(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);///< is not used depreceated

private:
	bool m_bPressed = false;///< Has the button been pressed
	bool m_bReleased = false;///< Has the button been released

public:
	bool isPressed();///< Has the button been pressed
	bool isReleased();///< Has the button been released

};

 
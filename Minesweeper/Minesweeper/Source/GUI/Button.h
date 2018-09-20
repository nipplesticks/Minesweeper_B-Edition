#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button : public sf::Drawable
{
private:
	static sf::Font		s_font;

	sf::RectangleShape	m_rect;
	sf::Text			m_text;
public:
	Button();
	void setBackgroundColor(int r, int g, int b, int a = 255);
	void setOutlineColor(int r, int g, int b, int a = 255);
	void setTextColor(int r, int g, int b, int a = 255);
	void setTextString(const std::string & str);
	void setPosition(int x, int y);
	void setButtonSize(int x, int y);
	void setTextSize(int px);
	void setOutlineThickness(int px);
	void setTexture(const sf::Texture & txt);
	bool isPressed(const sf::Vector2i & mp);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	void _rePositionText();

public:
	static void Init();
};
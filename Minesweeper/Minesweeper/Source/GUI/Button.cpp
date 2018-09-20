#include "Button.h"

sf::Font Button::s_font;

Button::Button()
{
	m_text.setFont(s_font);
	m_rect.setOutlineThickness(-2.0f);
}

void Button::setBackgroundColor(int r, int g, int b, int a)
{
	m_rect.setFillColor(sf::Color(r, g, b, a));
}

void Button::setOutlineColor(int r, int g, int b, int a)
{
	m_rect.setOutlineColor(sf::Color(r, g, b, a));
}

void Button::setTextColor(int r, int g, int b, int a)
{
	m_text.setFillColor(sf::Color(r, g, b, a));
}

void Button::setTextString(const std::string & str)
{
	m_text.setString(str);
	_rePositionText();
}

void Button::setPosition(int x, int y)
{
	m_rect.setPosition((float)x, (float)y);
	_rePositionText();
}

void Button::setButtonSize(int x, int y)
{
	m_rect.setSize(sf::Vector2f((float)x, (float)y));
	_rePositionText();
}

void Button::setTextSize(int px)
{
	m_text.setCharacterSize(px);
	_rePositionText();
}

void Button::setOutlineThickness(int px)
{
	m_rect.setOutlineThickness((float)px);
}

void Button::setTexture(const sf::Texture & txt)
{
	m_rect.setTexture(&txt);
}

bool Button::isPressed(const sf::Vector2i & mp)
{
	return m_rect.getGlobalBounds().contains((float)mp.x, (float)mp.y);
}

void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_rect, states);
	target.draw(m_text, states);
}

void Button::_rePositionText()
{
	sf::FloatRect tBox = m_text.getLocalBounds();
	sf::Vector2f origin;
	origin.x = (tBox.left + tBox.width) / 2.0f;
	origin.y = (tBox.top + tBox.height) / 2.0f;
	m_text.setOrigin(origin);

	sf::Vector2f tPos;
	tPos = m_rect.getPosition() + (m_rect.getSize() / 2.0f);
	m_text.setPosition(tPos);
}

void Button::Init()
{
	s_font.loadFromFile("Assets/mineFont.ttf");
}

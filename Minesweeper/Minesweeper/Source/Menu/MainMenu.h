#pragma once
#include "Options.h"
class MainMenu : public sf::Drawable
{
public:
	enum ButtonPressed
	{
		Play,
		Quit,
		None
	};

private:
	Button m_play;
	Button m_quit;
	Button m_options;
	Options m_optionState;
	bool m_insideOptions;
public:
	MainMenu();
	ButtonPressed MousePress(const sf::Vector2i & mp);
	Options::Settings getSettings() const;
	bool isInsideOptions() const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	Button _getStandardButton() const;
};
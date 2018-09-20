#include "MainMenu.h"

MainMenu::MainMenu()
{
	m_insideOptions = false;
	m_play = _getStandardButton();
	m_options = _getStandardButton();
	m_quit = _getStandardButton();

	int middle = 300 - 128;
	int startPos = 128;
	int offset = 64;

	m_play.setPosition(middle, startPos);
	m_options.setPosition(middle, startPos + 128 + offset);
	m_quit.setPosition(middle, startPos + 2 * (128 + offset));

	m_play.setTextString("PLAY");
	m_options.setTextString("SETTINGS");
	m_quit.setTextString("EXIT");
}

MainMenu::ButtonPressed MainMenu::MousePress(const sf::Vector2i & mp)
{
	MainMenu::ButtonPressed state = MainMenu::ButtonPressed::None;
	
	if (m_insideOptions)
		m_insideOptions = m_optionState.MousePress(mp);
	else
	{
		if (m_play.isPressed(mp))
			state = MainMenu::ButtonPressed::Play;
		else if (m_quit.isPressed(mp))
			state = MainMenu::ButtonPressed::Quit;
		else if (m_options.isPressed(mp))
			m_insideOptions = true;
	}

	return state;
}

Options::Settings MainMenu::getSettings() const
{
	return Options::s_currentSetting;
}

bool MainMenu::isInsideOptions() const
{
	return m_insideOptions;
}

void MainMenu::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	if (m_insideOptions)
	{
		target.draw(m_optionState, states);
	}
	else
	{
		target.draw(m_play, states);
		target.draw(m_options, states);
		target.draw(m_quit, states);
	}
}

Button MainMenu::_getStandardButton() const
{
	Button b;
	b.setBackgroundColor(128, 128, 128);
	b.setButtonSize(256, 128);
	b.setOutlineColor(55, 55, 55);
	b.setTextColor(126, 0, 0);
	b.setTextSize(40);
	return b;
}

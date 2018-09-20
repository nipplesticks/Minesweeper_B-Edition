#pragma once
#include "../GUI/Button.h"
#include <fstream>

class Options : public sf::Drawable
{
public:
	struct Settings
	{
		int nrOfBombs = 33;
		int gridX = 10;
		int gridY = 10;
	};

private:
	Button m_removeBombs;
	Button m_numberOfBombs;
	Button m_addBombs;

	Button m_removeGridX;
	Button m_gridX;
	Button m_addGridX;

	Button m_removeGridY;
	Button m_gridY;
	Button m_addGridY;

	Button m_back;

public:
	static Settings s_currentSetting;

public:
	Options();

	//Returns if still in options menu;
	bool MousePress(const sf::Vector2i & mp);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


private:
	Button _getStandardTextButton() const;
	Button _getStandardIncrementButton() const;
	void _loadLastSetting();
	void _saveLastSetting();
};
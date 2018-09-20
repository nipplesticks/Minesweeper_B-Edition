#include "Options.h"

Options::Settings Options::s_currentSetting;


Options::Options()
{
	m_removeBombs = _getStandardIncrementButton();
	m_numberOfBombs = _getStandardTextButton();
	m_addBombs = _getStandardIncrementButton();;

	m_removeGridX = _getStandardIncrementButton();;
	m_gridX = _getStandardTextButton();
	m_addGridX = _getStandardIncrementButton();;

	m_removeGridY = _getStandardIncrementButton();;
	m_gridY = _getStandardTextButton();
	m_addGridY = _getStandardIncrementButton();;

	m_back = _getStandardTextButton();

	int middle = 300 - 128;
	int startPos = 128;
	int offsetY = 32;
	
	int offsetX = 5;
	int removeXpos = 300 - 128 - 64 - offsetX;
	
	int addXpos = 300 + 128 + offsetX;

	m_numberOfBombs.setPosition(middle, startPos);
	m_removeBombs.setPosition(removeXpos, startPos);
	m_addBombs.setPosition(addXpos, startPos);

	m_gridX.setPosition(middle, startPos + 128 + offsetY);
	m_removeGridX.setPosition(removeXpos, startPos + 128 + offsetY);
	m_addGridX.setPosition(addXpos, startPos + 128 + offsetY);

	m_gridY.setPosition(middle, startPos + 2 * (128 + offsetY));
	m_removeGridY.setPosition(removeXpos, startPos + 2 * (128 + offsetY));
	m_addGridY.setPosition(addXpos, startPos + 2 * (128 + offsetY));

	m_back.setPosition(middle, startPos + 3 * (128 + offsetY));


	m_removeBombs.setTextString("-");
	m_addBombs.setTextString("+");
	m_removeGridX.setTextString("-");
	m_addGridX.setTextString("+");
	m_removeGridY.setTextString("-");
	m_addGridY.setTextString("+");
	m_back.setTextString("BACK");

	_loadLastSetting();
	
	m_numberOfBombs.setTextString("BOMBS: " + std::to_string(s_currentSetting.nrOfBombs));
	m_gridX.setTextString("GRID_X: " + std::to_string(s_currentSetting.gridX));
	m_gridY.setTextString("GRID_Y: " + std::to_string(s_currentSetting.gridY));

}

bool Options::MousePress(const sf::Vector2i & mp)
{
	if (m_back.isPressed(mp))
	{
		_saveLastSetting();
		return false;
	}
	else if (m_addBombs.isPressed(mp))
		s_currentSetting.nrOfBombs++;
	else if (m_removeBombs.isPressed(mp))
		s_currentSetting.nrOfBombs--;
	else if (m_addGridX.isPressed(mp))
		s_currentSetting.gridX++;
	else if (m_removeGridX.isPressed(mp))
		s_currentSetting.gridX--;
	else if (m_addGridY.isPressed(mp))
		s_currentSetting.gridY++;
	else if (m_removeGridY.isPressed(mp))
		s_currentSetting.gridY--;

	if (s_currentSetting.gridY < 5)
		s_currentSetting.gridY = 5;
	if (s_currentSetting.gridX < 5)
		s_currentSetting.gridX = 5;
	if (s_currentSetting.nrOfBombs < 1)
		s_currentSetting.nrOfBombs = 1;
	else if (s_currentSetting.nrOfBombs >= s_currentSetting.gridX * s_currentSetting.gridY)
		s_currentSetting.nrOfBombs = s_currentSetting.gridX * s_currentSetting.gridY - 1;

	m_numberOfBombs.setTextString("BOMBS: " + std::to_string(s_currentSetting.nrOfBombs));
	m_gridX.setTextString("GRID_X: " + std::to_string(s_currentSetting.gridX));
	m_gridY.setTextString("GRID_Y: " + std::to_string(s_currentSetting.gridY));


	return true;
}

void Options::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_removeBombs, states);
	target.draw(m_numberOfBombs , states);
	target.draw(m_addBombs, states);
	target.draw(m_removeGridX, states);
	target.draw(m_gridX, states);
	target.draw(m_addGridX, states);
	target.draw(m_removeGridY, states);
	target.draw(m_gridY, states);
	target.draw(m_addGridY, states);
	target.draw(m_back, states);
}

Button Options::_getStandardTextButton() const
{
	Button b;
	b.setBackgroundColor(128, 128, 128);
	b.setButtonSize(256, 64);
	b.setOutlineColor(55, 55, 55);
	b.setTextColor(126, 0, 0);
	b.setTextSize(32);
	return b;
}

Button Options::_getStandardIncrementButton() const
{
	Button b;
	b.setBackgroundColor(128, 128, 128);
	b.setButtonSize(64, 64);
	b.setOutlineColor(55, 55, 55);
	b.setTextColor(126, 0, 0);
	b.setTextSize(64);
	return b;
}

void Options::_loadLastSetting()
{
	std::string file;
	file = "Other/dataset.msbe";

	std::ifstream read;
	read.open(file);
	if (!read)
	{
		std::ofstream write;
		write.open(file);
		write << 33 << '\n';
		write << 10 << '\n';
		write << 10;
		write.close();
		read.open(file);
	}

	read >> s_currentSetting.nrOfBombs;
	read >> s_currentSetting.gridX;
	read >> s_currentSetting.gridY;

	read.close();
}

void Options::_saveLastSetting()
{
	std::string file;
	file = "Other/dataset.msbe";
	std::ofstream write;
	write.open(file);
	write << s_currentSetting.nrOfBombs << '\n';
	write << s_currentSetting.gridX << '\n';
	write << s_currentSetting.gridY;
	
	write.close();
}

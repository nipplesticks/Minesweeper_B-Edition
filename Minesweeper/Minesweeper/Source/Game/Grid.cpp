#include "Grid.h"
#include <iostream>
Grid::Grid()
{
	_init();
}

Grid::~Grid()
{
	_clean();
}

void Grid::Init(int sizeX, int sizeY, int bombs)
{
	_clean();
	m_width = sizeX;
	m_height = sizeY;
	m_totalUnrevealed = m_width * m_height;
	m_gameStats = GameStats{ bombs, bombs, bombs };
	_setupNewGrid();
	_loadHighScore();
	_initBarItems();
}

void Grid::Restart()
{
    Init(m_width, m_height, m_gameStats.BombsAtStart);
}

void Grid::Update(const sf::Vector2i & mp, float dt)
{
	m_drawHighlight = false;
	if (!m_wonGame && !m_lostGame)
	{
		if (m_gameStarted)
		{
			m_exactTimePassed += dt;
			m_timePassedSec = (int)m_exactTimePassed;
			m_time.setTextString(std::to_string(m_timePassedSec / 60) + ":" + std::to_string(m_timePassedSec % 60));
		}
		if (mp.x >= 0 && mp.y >= 32 && mp.x < m_width * 32 && mp.y < m_height * 32 + 32)
		{
			m_drawHighlight = true;
			m_highlight.setPosition((float)((int)(mp.x / 32) * 32), (float)((int)(mp.y / 32) * 32));
		}
	}
	else if (!m_saved && m_gameStarted)
		_saveHighScore();

}

bool Grid::LeftClick(const sf::Vector2i & mp)
{
	int index_X = -1;
	int index_Y = -1;
	if (mp.y - 32 >= 0)
	{
		index_X = mp.x / 32;
		index_Y = (mp.y - 32) / 32;
	}
	if (index_Y >= 0 && index_Y < m_height && index_X >= 0 && index_X < m_width &&
		!m_wonGame && !m_lostGame)
	{
		m_gameStarted = true;
		if (m_grid[index_X][index_Y].getState() == Tile::State::Unrevealed)
		{
			m_totalUnrevealed--;
			m_grid[index_X][index_Y].setState(Tile::State::Revealed);
			m_grid[index_X][index_Y].UpdateSprite();

			if (m_grid[index_X][index_Y].getType() == Tile::Type::Empty)
				_revealEmptyAround(index_X, index_Y);

			m_lostGame = m_grid[index_X][index_Y].getType() == Tile::Type::Bomb;
			if (m_lostGame)
			{
				_updateAndRevealAll();
				m_grid[index_X][index_Y].ForceTexture(TextureManager::g_BombPressed);
			}
			m_wonGame = m_gameStats.ActualBombsLeft == 0 && m_totalUnrevealed == m_gameStats.BombsAtStart;
		}
	}
	else
	{
		if (m_reset.isPressed(mp))
		{
			Init(m_width, m_height, m_gameStats.BombsAtStart);
		}
		else if (m_back.isPressed(mp))
		{
			return false;
		}
	}
	return true;
}

void Grid::RightClick(const sf::Vector2i & mp)
{
	int index_X = -1;
	int index_Y = -1;
	if (mp.y - 32 >= 0)
	{
		index_X = mp.x / 32;
		index_Y = (mp.y - 32) / 32;
	}
	if (index_Y >= 0 && index_Y < m_height && index_X >= 0 && index_X < m_width &&
		!m_wonGame && !m_lostGame)
	{
		m_gameStarted = true;
		int pb = 0;
		int ab = 0;

		if (m_grid[index_X][index_Y].getState() == Tile::State::Unrevealed)
		{
			m_grid[index_X][index_Y].setState(Tile::State::Flag);
			pb--;
		}
		else if (m_grid[index_X][index_Y].getState() == Tile::State::Flag)
		{
			m_grid[index_X][index_Y].setState(Tile::State::Unrevealed);
			pb++;
		}

		if (m_grid[index_X][index_Y].getType() == Tile::Type::Bomb)
		{
			ab = pb;
		}
		m_gameStats.ActualBombsLeft += ab;
		m_gameStats.PotentialBombsLeft += pb;
		m_grid[index_X][index_Y].UpdateSprite();
		std::cout << "Potential Bombs left:\t" << m_gameStats.PotentialBombsLeft << std::endl;
		std::cout << "Actual Bombs left:\t" << m_gameStats.ActualBombsLeft << std::endl;
		m_wonGame = m_gameStats.ActualBombsLeft == 0 && m_totalUnrevealed == m_gameStats.BombsAtStart;
		m_potBombsLeft.setTextString(std::to_string(m_gameStats.PotentialBombsLeft));
	}
}

bool Grid::isLost() const
{
	return m_lostGame;
}

bool Grid::isWon() const
{
	return m_wonGame;
}

void Grid::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_barBackground, states);
	target.draw(m_reset, states);
	target.draw(m_time, states);
	target.draw(m_back, states);
	target.draw(m_potBombsLeft, states);
	target.draw(m_highScoreButton, states);

	for (int i = 0; i < m_width; i++)
	{
		for (int k = 0; k < m_height; k++)
		{
			target.draw(m_grid[i][k], states);
		}
	}
	if (m_drawHighlight)
		target.draw(m_highlight, states);
}

void Grid::_init()
{
	_initGameItems();
}

void Grid::_initGameItems()
{
	m_drawHighlight = false;
	m_grid = nullptr;
	m_highlight.setFillColor(sf::Color(0, 0, 0, 0));
	m_highlight.setOutlineThickness(-2.0f);
	m_highlight.setOutlineColor(sf::Color(255, 0, 0));
	m_highlight.setSize(sf::Vector2f(32.0f, 32.0f));
	m_width = 0;
	m_height = 0;
	m_totalUnrevealed = 0;
	m_lostGame = false;
	m_wonGame = false;
	m_exactTimePassed = 0.0f;
	m_timePassedSec = 0;
}

void Grid::_initBarItems()
{
	m_barBackground.setPosition(0, 0);
	m_barBackground.setButtonSize(m_width * 32, 32);
	m_barBackground.setOutlineColor(0, 28, 0);
	m_barBackground.setBackgroundColor(0, 55, 0);
	m_barBackground.setTextColor(255, 255, 255, 28);
	m_barBackground.setTextSize(26);
	m_barBackground.setTextString("Minesweeper, B-Edition");


	int totalSize = m_width * 32;
	int middle = totalSize / 2;
	int sizeY = 32;

	int timeSize = (totalSize - (middle + 16)) / 2;
	int timeTsize = timeSize / 5;
	if (timeTsize > 26)
		timeTsize = 26;
	if (timeSize > 120)
		timeSize = 120;

	int backSize = (middle - 16) / 2;
	int backTsize = backSize / 4;
	if (backTsize > 26)
		backTsize = 26;

	m_reset.setPosition(middle - 16, 0);
	m_reset.setButtonSize(32, sizeY);
	m_reset.setTexture(TextureManager::g_Reset);
	m_reset.setOutlineThickness(0);
	m_reset.setBackgroundColor(255, 255, 255, 128);

	m_time.setPosition(totalSize - timeSize, 0);
	m_time.setButtonSize(timeSize, 32);
	m_time.setTextColor(55, 0, 0);
	m_time.setTextSize(timeTsize);
	m_time.setTextString("0:0");
	m_time.setBackgroundColor(0, 255, 0, 55);
	m_time.setOutlineColor(0, 0, 0);

	m_highScoreButton.setPosition(middle + 16, 0);
	m_highScoreButton.setButtonSize(timeSize, 32);
	m_highScoreButton.setTextColor(55, 0, 0);
	m_highScoreButton.setTextSize(timeTsize);
	m_highScoreButton.setBackgroundColor(0, 255, 0, 55);
	m_highScoreButton.setOutlineColor(0, 0, 0);

	m_back.setPosition(0, 0);
	m_back.setButtonSize(backSize, 32);
	m_back.setTextString("BACK");
	m_back.setTextSize(backTsize);
	m_back.setBackgroundColor(0, 255, 0, 55);
	m_back.setOutlineColor(0, 0, 0);
	m_back.setTextColor(55, 0, 0);

	m_potBombsLeft.setPosition(backSize, 0);
	m_potBombsLeft.setButtonSize(backSize, 32);
	m_potBombsLeft.setTextString(std::to_string(m_gameStats.PotentialBombsLeft));
	m_potBombsLeft.setTextSize(backTsize);
	m_potBombsLeft.setBackgroundColor(0, 255, 0, 55);
	m_potBombsLeft.setOutlineColor(0, 0, 0);
	m_potBombsLeft.setTextColor(55, 0, 0);

}

void Grid::_clean()
{
	if (m_grid)
	{
		for (int i = 0; i < m_width; i++)
		{
			delete[] m_grid[i];
		}
		delete[] m_grid;
		m_grid = nullptr;
		m_width = 0;
		m_height = 0;
		m_exactTimePassed = 0.0f;
		m_timePassedSec = 0;
		m_lostGame = false;
		m_wonGame = false;
		m_saved = false;
		m_highscore = 0;
		m_gameStarted = false;
	}
}

void Grid::_setupNewGrid()
{
	_allocGrid();
	_setTilePos();
	_placeBombs();
}

void Grid::_allocGrid()
{
	m_grid = new Tile*[m_width];
	for (int i = 0; i < m_width; i++)
	{
		m_grid[i] = new Tile[m_height];
	}
}

void Grid::_setTilePos()
{
	for (int i = 0; i < m_width; i++)
	{
		for (int k = 0; k < m_height; k++)
		{
			m_grid[i][k].setPosition(i * 32.0f, k * 32.0f + 32.0f);
		}
	}
}

void Grid::_placeBombs()
{
	for (int i = 0; i < m_gameStats.BombsAtStart; i++)
	{
		bool placed = false;
		while (!placed)
		{
			int x = rand() % m_width;
			int y = rand() % m_height;

			if (m_grid[x][y].getType() != Tile::Type::Bomb)
			{
				m_grid[x][y].setType(Tile::Type::Bomb);
				_placeNumbersAround(x, y);
				placed = true;
			}
		}
	}
}

void Grid::_revealEmptyAround(int x, int y)
{
	int iStart = -1;
	int iStop = 2;
	int kStart = -1;
	int kStop = 2;

	if (x == 0)
		iStart++;
	else if (x == m_width - 1)
		iStop--;
	if (y == 0)
		kStart++;
	else if (y == m_height - 1)
		kStop--;

	for (int i = iStart; i < iStop; i++)
	{
		for (int k = kStart; k < kStop; k++)
		{
			if (i == 0 && k == 0)
				continue;

			if (m_grid[i + x][k + y].getState() == Tile::State::Unrevealed)
			{
				if (m_grid[i + x][k + y].getType() != Tile::Type::Bomb)
				{
					m_totalUnrevealed--;
					m_grid[i + x][k + y].setState(Tile::State::Revealed);
					m_grid[i + x][k + y].UpdateSprite();

					if (m_grid[i + x][k + y].getType() == Tile::Type::Empty)
						_revealEmptyAround(i + x, k + y);
				}
			}
		}
	}
}

void Grid::_placeNumbersAround(int x, int y)
{
	int iStart = -1;
	int iStop = 2;
	int kStart = -1;
	int kStop = 2;

	if (x == 0)
		iStart++;
	else if (x == m_width - 1)
		iStop--;
	if (y == 0)
		kStart++;
	else if (y == m_height - 1)
		kStop--;

	for (int i = iStart; i < iStop; i++)
	{
		for (int k = kStart; k < kStop; k++)
		{
			if (i == 0 && k == 0)
				continue;

			if (m_grid[i + x][k + y].getType() == Tile::Type::Empty)
				m_grid[i + x][k + y].setType(Tile::Type::Number);
			m_grid[i + x][k + y].setNumberOfNearbyBombs(m_grid[i + x][k + y].getNumberOfNearbyBombs() + 1);
		}
	}
}

void Grid::_updateAndRevealAll()
{
	for (int i = 0; i < m_width; i++)
	{
		for (int k = 0; k < m_height; k++)
		{
			switch (m_grid[i][k].getState())
			{
			case Tile::State::Unrevealed:
				m_grid[i][k].setState(Tile::State::Revealed);
				m_grid[i][k].UpdateSprite();
				break;
			case Tile::State::Flag:
				if (m_grid[i][k].getType() != Tile::Type::Bomb)
					m_grid[i][k].ForceTexture(TextureManager::g_FlagFail);
				break;
			}
		}
	}
}

void Grid::_loadHighScore()
{
	std::string file;
	file = "Other/data" + std::to_string(m_width * m_height) + std::to_string(m_gameStats.BombsAtStart) + ".msbe";

	std::ifstream read;
	read.open(file);
	if (!read)
	{
		std::ofstream write;
		write.open(file);
		write << -1;
		write.close();
		read.open(file);
	}

	read >> m_highscore;
	read.close();

	if (m_highscore < 0)
	{
		m_highScoreButton.setTextString("HI:NA");
	}
	else
	{
		m_highScoreButton.setTextString(std::to_string(m_highscore / 60) + ":" + std::to_string(m_highscore % 60));
	}

}

void Grid::_saveHighScore()
{
	m_saved = true;
	if (m_wonGame && (m_timePassedSec < m_highscore || m_highscore == -1))
	{
		std::string file;
		file = "Other/data" + std::to_string(m_width * m_height) + std::to_string(m_gameStats.BombsAtStart) + ".msbe";
		std::ofstream write;
		write.open(file);
		write << m_timePassedSec;
		write.close();
	}
}

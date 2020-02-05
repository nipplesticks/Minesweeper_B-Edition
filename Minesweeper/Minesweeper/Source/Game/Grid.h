#pragma once
#include "Tile.h"
#include "../GUI/Button.h"
#include <fstream>

class Grid : public sf::Drawable
{
private:
	//Game Vars
	struct GameStats
	{
		int BombsAtStart = 0;
		int PotentialBombsLeft = 0;
		int ActualBombsLeft = 0;
	};

	Tile**				m_grid;
	sf::RectangleShape m_highlight;

	bool		m_drawHighlight;
	int			m_width;
	int			m_height;
	int			m_totalUnrevealed;

	bool		m_lostGame;
	bool		m_wonGame;

	GameStats	m_gameStats;
	float		m_exactTimePassed;
	int			m_timePassedSec;
	//Game Vars end

	// Bar vars
	Button m_barBackground;
	Button m_potBombsLeft;
	Button m_time;
	Button m_reset;
	Button m_back;
	Button m_highScoreButton;

	bool m_gameStarted;
	int m_highscore;
	bool m_saved;

public:
	Grid();
	~Grid();
	void Init(int sizeX, int sizeY, int bombs);
  void Restart();
	void Update(const sf::Vector2i & mp, float dt);

	// will return false if not allowed to continue
	bool LeftClick(const sf::Vector2i & mp);
	void RightClick(const sf::Vector2i & mp);

	bool isLost() const;
	bool isWon() const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	void _init();
	void _initGameItems();
	void _initBarItems();
	void _clean();
	void _setupNewGrid();
	void _allocGrid();
	void _setTilePos();
	void _placeBombs();
	void _revealEmptyAround(int x, int y);
	void _placeNumbersAround(int x, int y);
	void _updateAndRevealAll();
	void _loadHighScore();
	void _saveHighScore();
};
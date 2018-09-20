#include "Tile.h"

Tile::Tile()
{
	m_tileSprite.setTexture(TextureManager::g_Undiscovered);

	m_state = Tile::State::Unrevealed;
	m_type = Tile::Type::Empty;
	m_nrOfNearbyBombs = 0;
}

void Tile::UpdateSprite()
{
	if (m_state == Tile::State::Revealed)
	{
		switch (m_type)
		{
		case Tile::Type::Bomb:
			m_tileSprite.setTexture(TextureManager::g_Bomb);
			break;
		case Tile::Type::Empty:
			m_tileSprite.setTexture(TextureManager::g_Empty);
			break;
		case Tile::Type::Number:
			m_tileSprite.setTexture(TextureManager::g_Number[m_nrOfNearbyBombs - 1]);
			break;
		}
	}
	else if (m_state == Tile::State::Flag)
	{
		m_tileSprite.setTexture(TextureManager::g_Flag);
	}
	else
	{
		m_tileSprite.setTexture(TextureManager::g_Undiscovered);
	}
}

void Tile::setPosition(float x, float y)
{
	m_tileSprite.setPosition(x, y);
}

void Tile::setState(State state)
{
	m_state = state;
}

void Tile::setType(Type type)
{
	m_type = type;
}

void Tile::setNumberOfNearbyBombs(int nrOfBombs)
{
	m_nrOfNearbyBombs = nrOfBombs;
}

void Tile::ForceTexture(sf::Texture & txt)
{
	m_tileSprite.setTexture(txt);
}

Tile::State Tile::getState() const
{
	return m_state;
}

Tile::Type Tile::getType() const
{
	return m_type;
}

int Tile::getNumberOfNearbyBombs() const
{
	return m_nrOfNearbyBombs;
}

void Tile::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_tileSprite, states);
}

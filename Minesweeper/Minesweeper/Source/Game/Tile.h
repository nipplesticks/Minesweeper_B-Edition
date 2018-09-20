#pragma once
#include "TextureManager.h"


class Tile : public sf::Drawable
{
public:
	enum State
	{
		Revealed,
		Unrevealed,
		Flag
	};
	enum Type
	{
		Bomb,
		Number,
		Empty
	};
private:
	sf::Sprite m_tileSprite;
	Tile::State m_state;
	Tile::Type m_type;
	int m_nrOfNearbyBombs;
public:
	Tile();

	void UpdateSprite();

	void setPosition(float x, float y);
	void setState(Tile::State state);
	void setType(Tile::Type type);
	void setNumberOfNearbyBombs(int nrOfBombs);
	void ForceTexture(sf::Texture & txt);

	Tile::State getState() const;
	Tile::Type getType() const;
	int getNumberOfNearbyBombs() const;
	
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
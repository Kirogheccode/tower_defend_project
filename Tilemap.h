#pragma once
#include <SFML/Graphics.hpp>
class Tilemap
{
private:
	sf::Texture m_TilemapTexture;
	sf::Sprite m_TilemapSprite;

public:
	enum TileType
	{
		Null = -1,
		Camp,
		Spawn,
		End,
		Path
	};
	
	bool Available; // if the tile is available for building
	void setAvailable(bool newState) 
	{
		Available = newState;
	}
};


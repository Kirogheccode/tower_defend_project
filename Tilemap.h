#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>
#include "MathSupport.h"

// a square 
class TileOption : public sf::Drawable
{
public :
	enum TileType {
		Aesthetic = 0,
		Path = 1,
		TowerBase = 2,
		Spawn = 3,
		End = 4
	};

private:
	sf::Sprite m_Sprite;
	TileType m_eTileType; 

public:

	void SetSprite(const sf::Sprite& sprite) 
	{ 
		m_Sprite = sprite; 
	}

	const sf::Sprite& getSprite() const 
	{ 
		return m_Sprite; 
	}
	
	void setPosition(const sf::Vector2f& position) 
	{ 
		m_Sprite.setPosition(position); 
	}

	TileType GetTyleType() const 
	{ 
		return m_eTileType; 
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	{
		target.draw(m_Sprite, states);
	}
};

typedef std::pair<std::vector<sf::Vector2i>, TileOption*> tileArchitect;
class TileMap
{
protected:
	tileArchitect AstheticType;
	tileArchitect PathType;
	tileArchitect TowerBaseType;

	sf::Vector2i EndCoor;
	sf::Vector2i SpawnCoor;

public:
	void Draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
	}
	sf::Vector2i GetEndCoordinates() const
	{
		return EndCoor;
	}
	

};


class Path
{
public:
	struct PathTile
	{
		TileOption* pCurrentTile; // Current tile in the path
		TileOption* pNextTile; // Next tile in the path, if any
	};

	std::vector<PathTile> m_Tiles; // List of tiles in the path
	
	PathTile& back()
	{
		return m_Tiles.back();
	}

	void emplace_back()
	{
		m_Tiles.emplace_back();
	}

	bool ContainedInPath(const sf::Vector2i& coordinates)
	{
		for (const PathTile& pathTile : m_Tiles)
		{
			if (MathSupport::BoardCoordinates(pathTile.pCurrentTile->getSprite()) == coordinates)
			{
				return true;
			}
		}
		return false;
	}

	void VisitPathNeighbors(const TileMap PlayingMap, TileOption* EndPoint)
	{
		const sf::Vector2i vCurrentTilePosition = MathSupport::BoardCoordinates((*this).back().pCurrentTile->getSprite());

		const sf::Vector2i vNorthCoords(vCurrentTilePosition.x, vCurrentTilePosition.y - 1);
		const sf::Vector2i vEastCoords(vCurrentTilePosition.x + 1, vCurrentTilePosition.y);
		const sf::Vector2i vSouthCoords(vCurrentTilePosition.x, vCurrentTilePosition.y + 1);
		const sf::Vector2i vWestCoords(vCurrentTilePosition.x - 1, vCurrentTilePosition.y);

		if (PlayingMap.GetEndCoordinates() == vNorthCoords || PlayingMap.GetEndCoordinates() == vEastCoords || PlayingMap.GetEndCoordinates() == vSouthCoords || PlayingMap.GetEndCoordinates() == vWestCoords)
		{
			// Set the last tile in our current path to point to the next tile
			this->back().pNextTile = EndPoint;

			// Add the next tile, and set it.
			PathTile newTile = this->m_Tiles.emplace_back();
			newTile.pCurrentTile = EndPoint;
			this->m_Tiles.push_back(newTile);

			// If any of our paths are next to the end tile, they should probably go straight to end and terminate.
			// If we didn't return here, we could move around the end tile before going into it.
			return;
		}

		//const std::vector<Entity>& pathTiles = GetListOfTiles(TileOption::TileType::Path);

		for (const PathTile& curPathTile : this->m_Tiles)
		{
			const sf::Vector2i vPathTileCoords = MathSupport::BoardCoordinates(curPathTile.pCurrentTile->getSprite());

			// If the path already contains this tile, skip it
			if (ContainedInPath(vPathTileCoords))
			{
				continue;
			}

			// Doesn't contain the coordinates, check if it's a neighbor
			if (vPathTileCoords == vNorthCoords || vPathTileCoords == vEastCoords || vPathTileCoords == vSouthCoords || vPathTileCoords == vWestCoords)
			{
				// you're a neighbor, and we havent visisted you yet

				// Create a new path (so that we can find multiple paths recursively)
				Path newPath = (*this);
				// Set the last tile in our current path to point to the next tile
				newPath.back().pNextTile = curPathTile.pCurrentTile;
				// Add the next tile, and set it.
				PathTile& newTile = newPath.m_Tiles.emplace_back();
				newTile.pCurrentTile = curPathTile.pCurrentTile;

				newPath.VisitPathNeighbors(PlayingMap, EndPoint);
			}
		}
	}

};






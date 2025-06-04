#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace std;
using namespace sf;

class Map: public sf::Drawable, public sf::Transformable
{
	VertexArray m_vertices;

	Texture m_texture;

	vector<int> indexTexture;

	const string Path = "IMGS/Map/Grass/GrassTileSet.png";

	Vector2u tileSize = Vector2u(32, 32);

	int Width = 1, Height = 1;

	const int mapWidth = 1920;
	const int mapHeight = 1080; 

public:
	void printInfo();//For Debugging

	int Ceiling(int,int);

	void InitializeMap();

	void LoadMap();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the entity's transform -- combine it with the one that was passed by the caller
		states.transform *= getTransform(); // getTransform() is defined by sf::Transformable

		// apply the texture
		states.texture = &m_texture;

		// you may also override states.shader or states.blendMode if you want

		// draw the vertex array
		target.draw(m_vertices, states);
	}
};


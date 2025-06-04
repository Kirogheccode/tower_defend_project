#include "Map.h"
#include <iostream>

void Map::printInfo()
{
	cout << "Width: " << Width << endl;
	cout << "Height: " << Height << endl;

	for (int i = 0;i < Width * Height;i++)
	{
		if (i % Width == 0)
			cout << endl;

		cout << indexTexture[i] << " ";
	}
}

int Map::Ceiling(int x, int y) //Ceiling(x/y)
{
	if (x % y != 0)
		return x / y + 1;
	return x / y;
}

void Map::InitializeMap()
{
	//Loading texture
	if (!m_texture.loadFromFile(Path))
	{
		cout << "Failed to load map" << endl;
		return;
	}

    //How many neccessary tiles in row (Width) and column (Height) to cover the map
	Width = Ceiling(mapWidth, tileSize.x);
	Height = Ceiling(mapHeight, tileSize.y);

	// Set 1D Dimension array for the map
	indexTexture.resize(Width * Height);
	fill(indexTexture.begin(), indexTexture.end(), 0);

	//Set Path for 1D Dimesion array (Index[i] = 1);
	int Y = Width;//Set Vertical Path
	int X = Height;//Set Horizontal Path

	// Path is intersection in the middle of the map
	while (Y <= Width * Height)
	{
		indexTexture[(Y*2 - Width)/2] = 1;
		indexTexture[(Y*2 - Width)/2 - 1] = 1;
		Y += Width;
	}
	for (int i = 0;i < Width;i++)
	{
		indexTexture[((X / 2) * Width)+i] = 1;
		indexTexture[(((X - 1) / 2) * Width)+i] = 1;
	}
	//Set vertex for to draw

	m_vertices.setPrimitiveType(Triangles);
	m_vertices.resize(Width * Height * 6);
	// Therefore, we need 6 vertices per tile, we also have width * height needed tiles 
    // Draw map based on triagles (1 triangle = 3 vertices, we need 2 combining triangles to draw 1 tile)
	//  => The total vertices: Width * Height * 6
}

void Map::LoadMap()
{
	for (int i = 0 ; i < Width ; i++)
	{
		for (int j = 0 ; j < Height ; j++)
		{
			//Get current tile number
			int tileNumber = indexTexture[i + j * Width];

			//Find positon of current tile in tileSet texture, basing on tileNumber
			int tu = tileNumber % (m_texture.getSize().x / tileSize.x);//corresponding to X
			int tv = tileNumber / (m_texture.getSize().x / tileSize.y);//corresponding to Y

			//Get a pointer to the triangales' vertices of current tile
			//Each tile occpies 6 consecutive memory cells (correspond to 6 vertices)
			//=> Can access to 5 remaining vertices by the first vertex with index (i+j*Width)*6
			Vertex* triangles = &m_vertices[(i + j * Width) * 6];

			//Define 6 corners of the tile
			triangles[0].position = Vector2f((float)i* tileSize.x, (float)j * tileSize.y);
			triangles[1].position = Vector2f((float)(i + 1) * tileSize.x, (float)j * tileSize.y);
			triangles[2].position = Vector2f((float)i * tileSize.x, (float)(j + 1) * tileSize.y);
			triangles[3].position = Vector2f((float)i * tileSize.x, (float)(j + 1) * tileSize.y);
			triangles[4].position = Vector2f((float)(i + 1) * tileSize.x, (float)j * tileSize.y);
			triangles[5].position = Vector2f((float)(i + 1) * tileSize.x, (float)(j + 1) * tileSize.y);
			
		    //Define 6 matching texture coordinates
			triangles[0].texCoords = Vector2f((float)tu * tileSize.x, (float)tv * tileSize.y);
			triangles[1].texCoords = Vector2f((float)(tu + 1) * tileSize.x, (float)tv * tileSize.y);
			triangles[2].texCoords = Vector2f((float)tu * tileSize.x, (float)(tv + 1) * tileSize.y);
			triangles[3].texCoords = Vector2f((float)tu * tileSize.x, (float)(tv + 1) * tileSize.y);
			triangles[4].texCoords = Vector2f((float)(tu + 1) * tileSize.x, (float)tv * tileSize.y);
			triangles[5].texCoords = Vector2f((float)(tu + 1) * tileSize.x, (float)(tv + 1) * tileSize.y);
		}
	}
}

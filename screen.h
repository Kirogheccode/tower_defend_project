#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Screen
{
private:
	Texture texture;
	Font font;

	Sprite sprite;

	float width;
	float height;

public:
	Screen(float width, float height, string filepath);

	void setSpriteRect(float frame_width, float frame_height, int column, int row);

	void draw(float x, float y, RenderWindow& window);

	~Screen();
};

class Button
{
private:
	Texture texture;
	Texture hower_texture;

	Sprite sprite;

	float width;
	float height;

	bool isHovered = false;

public:
	Button(float width, float height, string filepath, string hower_filepath);

	bool handleinput(Vector2f& mousePos);

	void draw(float x, float y, RenderWindow& window);
};
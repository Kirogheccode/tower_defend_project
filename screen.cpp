#include <SFML/Graphics.hpp>
#include <iostream>

#include "screen.h"

using namespace std;
using namespace sf;

Screen::Screen(float x, float y, string filepath)
{
	texture.loadFromFile(filepath);
}

void Screen::draw(RenderWindow& window)
{
	Sprite sprite;
	sprite.setTexture(texture);

	window.draw(sprite);
}

Screen::~Screen() {}
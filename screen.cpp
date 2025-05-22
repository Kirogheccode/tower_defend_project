#include <SFML/Graphics.hpp>
#include <iostream>

#include "screen.h"

using namespace std;
using namespace sf;

//Screen
Screen::Screen(float width, float height, string filepath)
{
	this->width = width;
	this->height = height;

	texture.loadFromFile(filepath);
}

void Screen::draw(float x, float y, RenderWindow& window)
{
	Sprite sprite;
	sprite.setPosition(x, y);
	sprite.setTexture(texture);

	window.draw(sprite);
}

Screen::~Screen() {}

//Button
void Button::handleinputback(RenderWindow& window)
{
}


void Button::handleinputdraw(RenderWindow& window, Screen& new_screen)
{
}
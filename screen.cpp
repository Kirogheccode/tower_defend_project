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

void Screen::setSpriteRect(float frame_width, float frame_height, int column, int row)
{
    sprite.setTextureRect(sf::IntRect(column * frame_width, row * frame_height, frame_width, frame_height));
}

void Screen::draw(float x, float y, RenderWindow& window)
{
	sprite.setPosition(x, y);
	sprite.setTexture(texture);

	float scaleX = window.getSize().x / width;
	float scaleY = window.getSize().y / height;

	sprite.scale(scaleX, scaleY);

	window.draw(sprite);
}

Screen::~Screen() {}

//Button
Button::Button(float width, float height, string filepath, string hower_filepath)
{
	this->width = width;
	this->height = height;

	texture.loadFromFile(filepath);
	hower_texture.loadFromFile(hower_filepath);
}

bool Button::handleinput(Vector2f& mousePos)
{
    if (sprite.getGlobalBounds().contains(mousePos))
    {
        if (!isHovered)
        {
            sprite.setTexture(hower_texture);
            isHovered = true;
        }

        if (Mouse::isButtonPressed(Mouse::Button::Left))
        {
            return true;
        }
    }
    else
    {
        if (isHovered)
        {
            sprite.setTexture(texture);
            isHovered = false;
        }
    }

	return false;
}

void Button::draw(float x, float y, RenderWindow& window)
{
	sprite.setPosition(x, y);
	sprite.setTexture(texture);

	window.draw(sprite);
}
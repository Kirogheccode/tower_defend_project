#include <SFML/Graphics.hpp>
#include <iostream>

#include "screen.h"

using namespace std;
using namespace sf;

//Screen
Screen::Screen(string filepath) 
{
    width = 0;
    height = 0;

    if (!texture.loadFromFile(filepath))
    {
        cout << "Failed to load screen png" << endl;
        return;
    }

    this->width = texture.getSize().x;
    this->height = texture.getSize().y;

    sprite.setTexture(texture);
}

void Screen::setSize(float width, float height)
{
    this->width = width;
    this->height = height;
}

void Screen::setSpriteRect(float frame_width, float frame_height, int column, int row)
{
    sprite.setTextureRect(IntRect(
        static_cast<int>(column * frame_width),
        static_cast<int>(row * frame_height),
        static_cast<int>(frame_width),
        static_cast<int>(frame_height)
    ));
}

void Screen::draw(float x, float y, RenderWindow& window)
{
	sprite.setPosition(x, y);

	float scaleX = window.getSize().x / width;
	float scaleY = window.getSize().y / height;

	sprite.setScale(scaleX, scaleY);

	window.draw(sprite);    
}

Screen::~Screen() {}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Button
Button::Button(string filepath, string hower_filepath) 
{
    width = 0;
    height = 0;

    if (!texture.loadFromFile(filepath))
    {
        cout << "Failed to load screen png" << endl;
        return;
    }

    if (!hower_texture.loadFromFile(hower_filepath))
    {
        cout << "Failed to load screen png" << endl;
        return;
    }

    this->width = texture.getSize().x;
    this->height = texture.getSize().y;

    sprite.setTexture(texture);
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

void Button::setSize(float width, float height)
{
    this->width = width;
    this->height = height;
}

void Button::setSpriteRect(float frame_width, float frame_height, int column, int row)
{
    sprite.setTextureRect(sf::IntRect(column * frame_width, row * frame_height, frame_width, frame_height));
}

void Button::draw(float x, float y, RenderWindow& window)
{
	sprite.setPosition(x, y);

	window.draw(sprite);
}

Button::~Button() {}
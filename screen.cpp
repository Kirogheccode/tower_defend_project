#include "screen.h"

Screen::Screen(const std::string& filepath)
    : width(width), height(height)
{
    texture.loadFromFile(filepath);
    width = texture.getSize().x;
    height = texture.getSize().y;
}

void Screen::draw(float x, float y, sf::RenderWindow& window)
{
    sprite.setPosition(x, y);
    sprite.setTexture(texture);
    window.draw(sprite);
}

void Screen::setScale(sf::RenderWindow& window)
{
    float scaleX = window.getSize().x / width;
    float scaleY = window.getSize().y / height;

    sprite.setScale(scaleX, scaleY);
}
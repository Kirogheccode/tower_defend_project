#include "screen.h"

Screen::Screen(float width, float height, const std::string& filepath)
    : width(width), height(height)
{
    texture.loadFromFile(filepath);
}

void Screen::draw(float x, float y, sf::RenderWindow& window)
{
    sf::Sprite sprite;
    sprite.setPosition(x, y);
    sprite.setTexture(texture);
    window.draw(sprite);
}
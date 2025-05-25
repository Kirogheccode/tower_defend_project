#include "screen.h"

using namespace sf;

// ==== Screen ====
Screen::Screen(float width, float height, const std::string& filepath)
    : width(width), height(height)
{
    texture.loadFromFile(filepath);
}

void Screen::draw(float x, float y, RenderWindow& window)
{
    Sprite sprite;
    sprite.setPosition(x, y);
    sprite.setTexture(texture);
    window.draw(sprite);
}

// ==== Button ====
Button::Button(const std::string& imagePath, float x, float y)
{
    texture.loadFromFile(imagePath);
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}

void Button::draw(RenderWindow& window)
{
    window.draw(sprite);
}

void Button::update(RenderWindow& window)
{
    if (sprite.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window)))) {
        sprite.setColor(Color(200, 200, 200)); // Hover effect
    }
    else {
        sprite.setColor(Color(255, 255, 255));
    }
}

bool Button::isClicked(RenderWindow& window, Event& event)
{
    if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
        Vector2f mousePos = Vector2f(Mouse::getPosition(window));
        return sprite.getGlobalBounds().contains(mousePos);
    }
    return false;
}

void Button::setScale(float scaleX, float scaleY)
{
    sprite.setScale(scaleX, scaleY);
}

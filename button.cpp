#include "button.h"

Button::Button(const std::string& imagePath, float x, float y)
{
    texture.loadFromFile(imagePath);
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}

void Button::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void Button::update(sf::RenderWindow& window)
{
    if (sprite.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window)))) {
        sprite.setColor(sf::Color(200, 200, 200)); // Hover effect
    }
    else {
        sprite.setColor(sf::Color(255, 255, 255));
    }
}

bool Button::isClicked(sf::Vector2f mousePos, sf::Event& event)
{
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        return sprite.getGlobalBounds().contains(mousePos);
    }
    return false;
}

void Button::setScale(float scaleX, float scaleY)
{
    sprite.setScale(scaleX, scaleY);
}

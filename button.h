#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

class Button {
public:
    Button(const std::string& imagePath, float x, float y);

    Button(const std::string& imagePath, const std::string& pressedPath, float x, float y);

    void draw(sf::RenderWindow& window);

    void update(sf::RenderWindow& window);

    bool isClicked(sf::Vector2f mousePos, sf::Event& event);

    void setScale(float scaleX, float scaleY);

private:
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif

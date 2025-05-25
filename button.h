#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

class Button {
public:
    Button(const std::string& imagePath, float x, float y);
    void draw(sf::RenderWindow& window);
    void update(sf::RenderWindow& window);
    bool isClicked(sf::RenderWindow& window, sf::Event& event);
    void setScale(float scaleX, float scaleY);
private:
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif
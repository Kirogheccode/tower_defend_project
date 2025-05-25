#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>

class Screen {
public:
    Screen(float width, float height, const std::string& filepath);
    void draw(float x, float y, sf::RenderWindow& window);
private:
    float width;
    float height;
    sf::Texture texture;
};

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

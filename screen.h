#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>
#include <string>

class Screen {
public:
    Screen(const std::string& filepath);

    void draw(float x, float y, sf::RenderWindow& window);

    void setScale(sf::RenderWindow& window);

private:
    float width;
    float height;

    sf::Texture texture;
    sf::Sprite sprite;
};
#endif

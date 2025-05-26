#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>
#include <string>

class Screen {
public:
    Screen(float width, float height, const std::string& filepath);
    void draw(float x, float y, sf::RenderWindow& window);
private:
    float width;
    float height;
    sf::Texture texture;
};
#endif

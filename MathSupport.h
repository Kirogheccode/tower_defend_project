#pragma once
#include <SFML/Graphics.hpp>

namespace MathSupport
{
    // get length of a 2D vector
    float Length(const sf::Vector2f&);

    // take unit vector  
    sf::Vector2f Normalize(const sf::Vector2f&);

    sf::Vector2f GetPosition(sf::Sprite);
    
    sf::Vector2i BoardCoordinates(sf::Sprite);
}
#include "MathSupport.h"

// --- Get length of a 2D vector ---
float MathSupport::Length(const sf::Vector2f& vec)
{
    float fLength = sqrt(vec.x * vec.x + vec.y * vec.y);
    return fLength;
}


// --- Take unit vector ---  
sf::Vector2f MathSupport::Normalize(const sf::Vector2f& vec)
{
    float fLength = Length(vec);
    sf::Vector2f vUnit(vec.x / fLength, vec.y / fLength);
    return vUnit;
}

sf::Vector2f MathSupport::GetPosition(sf::Sprite sprite)
{
    return sprite.getPosition();
}

sf::Vector2i MathSupport::BoardCoordinates(sf::Sprite sprite)
{
    return sf::Vector2i(GetPosition(sprite).x / 160, GetPosition(sprite).y / 160);
}
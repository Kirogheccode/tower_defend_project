
#pragma once
#include <SFML/Graphics.hpp>

namespace MathSupport
{
   // get length of a 2D vector
   float Length(const sf::Vector2f& vec)
   {
        float fLength = sqrt(vec.x * vec.x + vec.y * vec.y);
        return fLength;
   }

   // take unit vector  
   sf::Vector2f Normalize(const sf::Vector2f& vec)
   {
         float fLength = Length(vec);
         sf::Vector2f vUnit(vec.x / fLength, vec.y / fLength);
         return vUnit;
    }

   sf::Vector2f GetPosition(sf::Sprite sprite)
   {
       return sprite.getPosition();
   }

   sf::Vector2i BoardCoordinates(sf::Sprite sprite)
   {
       return sf::Vector2i(GetPosition(sprite).x / 160, GetPosition(sprite).y / 160);
   }

}



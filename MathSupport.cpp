#include "MathSupport.h"

// --- Tính độ dài của vector 2 chiều ---
float MathSupport::Length(const sf::Vector2f& vec)
{
    float fLength = sqrt(vec.x * vec.x + vec.y * vec.y);
    return fLength;
}


// --- Chuẩn hóa vector (lấy vector đơn vị) ---
sf::Vector2f MathSupport::Normalize(const sf::Vector2f& vec)
{
    float fLength = Length(vec);
    sf::Vector2f vUnit(vec.x / fLength, vec.y / fLength);
    return vUnit;
}


// --- Lấy vị trí của sprite ---
sf::Vector2f MathSupport::GetPosition(sf::Sprite sprite)
{
    return sprite.getPosition();
}


// --- Lấy tọa độ ô lưới dựa theo vị trí sprite ---
sf::Vector2i MathSupport::BoardCoordinates(sf::Sprite sprite)
{
    return sf::Vector2i(GetPosition(sprite).x / 160, GetPosition(sprite).y / 160);
}

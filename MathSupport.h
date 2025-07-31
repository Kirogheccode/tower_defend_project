#pragma once
#include <SFML/Graphics.hpp>

namespace MathSupport
{
    // Tính độ dài (magnitude) của vector 2 chiều
    float Length(const sf::Vector2f&);

    // Chuẩn hóa vector (trả về vector đơn vị cùng hướng)
    sf::Vector2f Normalize(const sf::Vector2f&);

    // Lấy vị trí của một sprite
    sf::Vector2f GetPosition(sf::Sprite);

    // Trả về tọa độ lưới từ vị trí của sprite (giả sử mỗi ô lưới là 160x160)
    sf::Vector2i BoardCoordinates(sf::Sprite);
}

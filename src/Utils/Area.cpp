#include "Area.hpp"

Utils::Area::Area()
{
}

void Utils::Area::setArea(sf::Vector2f topLeft, sf::Vector2f bottomRight)
{
    m_top_left = topLeft;
    m_bottom_right = bottomRight;
}

bool Utils::Area::isInArea(sf::Vector2i position)
{
    return position.x >= m_top_left.x && position.x <= m_bottom_right.x &&
        position.y >= m_top_left.y && position.y <= m_bottom_right.y;
}

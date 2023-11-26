#include "Area.hpp"

Utils::Area::Area()
{
}

void Utils::Area::setArea(sf::Vector2i tl, sf::Vector2i br)
{
    m_top_left = tl;
    m_bottom_right = br;
}

bool Utils::Area::isInArea(sf::Vector2i position)
{
    return position.x >= m_top_left.x && position.x <= m_bottom_right.x &&
        position.y >= m_top_left.y && position.y <= m_bottom_right.y;
}

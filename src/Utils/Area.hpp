#pragma once
#include <SFML/Graphics.hpp>

namespace Utils
{
    class Area
    {
    private:
        sf::Vector2f m_top_left;
        sf::Vector2f m_bottom_right;
    public:
        float width;
        float height;
    public:
        Area();
        void setArea(sf::Vector2f topLeft, sf::Vector2f bottomRight);
        bool isInArea(sf::Vector2i position);
    };
}

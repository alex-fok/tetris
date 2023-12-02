#pragma once
#include <SFML/Graphics.hpp>

namespace Utils
{
    class Area
    {
    private:
        sf::Vector2i m_top_left;
        sf::Vector2i m_bottom_right;
    protected:
        float width;
        float height;
    public:
        Area();
        void setArea(sf::Vector2i tl, sf::Vector2i br);
        bool isInArea(sf::Vector2i position);
    };
}

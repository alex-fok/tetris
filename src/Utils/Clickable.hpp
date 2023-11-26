#pragma once
#include <SFML/Graphics.hpp>
#include "Area.hpp"

namespace Utils
{
    class Clickable : public Area
    {
    public:
        Clickable();
        virtual void handleClick(sf::Vector2i position);
    };
}

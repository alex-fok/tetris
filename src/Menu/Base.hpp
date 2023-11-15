#pragma once
#include <SFML/Graphics.hpp>

namespace Menu
{
    class Base
    {
    protected:
        sf::RenderWindow *m_window;
        sf::RectangleShape m_container;
    public:
        Base(sf::RenderWindow *w, sf::Vector2f v);
        void render();
    };
}

#pragma once
#include <SFML/Graphics.hpp>
#include "../Resources/FontCollection.hpp"
namespace Menu
{
    class Base
    {
    protected:
        Resources::FontCollection fontCollection;
        sf::RenderWindow *m_window;
        sf::RectangleShape m_container;
        sf::Text m_title;
    public:
        Base(sf::RenderWindow *w, sf::Vector2f v, const char *title);
        void renderBase();
        virtual void render();
    };
}

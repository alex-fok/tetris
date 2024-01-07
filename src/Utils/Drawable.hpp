#pragma once
#include <SFML/Graphics.hpp>
#include "Area.hpp"
#include "Clickable.hpp"

namespace Utils
{
    class Drawable : public Area
    {
    protected:
        sf::RenderWindow *m_window;
    public:
        Clickable **clickables;
        unsigned int clickableCount;
        Drawable(sf::RenderWindow *w);
        void setClickables(Clickable **c, unsigned int size);
        Clickable **getClickables();
        virtual void render();
        void draw(const sf::Drawable &d);
        ~Drawable();
    };
}

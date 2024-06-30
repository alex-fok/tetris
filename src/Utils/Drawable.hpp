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
        int clickableCount;
        Drawable();
        Drawable(sf::RenderWindow *w);
        void setClickables(Clickable **c, int size);
        Clickable **getClickables();
        void clearClickables();
        virtual void render();
        void draw(const sf::Drawable &d);
        ~Drawable();
    };
}

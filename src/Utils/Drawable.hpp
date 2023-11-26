#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Area.hpp"
#include "Clickable.hpp"

namespace Utils
{
    class Drawable : public Area
    {
    protected:
        sf::RenderWindow *m_window;
        std::vector<Clickable *> m_clickables;
    public:
        Drawable(sf::RenderWindow *w);
        void addClickable(Clickable *c);
        std::vector<Clickable *> getClickables();
        virtual void render();
        void draw(const sf::Drawable &d);
    };
}

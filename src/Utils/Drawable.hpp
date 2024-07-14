#pragma once
#include <SFML/Graphics.hpp>
#include "Area.hpp"

namespace Utils
{
    class Drawable : public Area
    {
    protected:
        sf::RenderWindow *m_window;
        sf::Text m_content;
    public:
        Drawable **drawables;
        int drawableCount;
        Drawable();
        Drawable(sf::RenderWindow *w);
        sf::Text getDrawable();
        virtual void setPosition(sf::Vector2f position);
        void setDrawables(Drawable **, int size);
        void setGridPositions();
        void setListPositions(float x, float offsetTop);
        void clearDrawables();
        virtual void handleClick();
        virtual void handleHover();
        virtual void render();
        void draw(const sf::Drawable &d);
        ~Drawable();
    };
}

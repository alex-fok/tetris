#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Drawable.hpp"

namespace Utils
{
    class Layer
    {
    private:
        sf::RenderWindow *m_window;
        std::vector<Drawable *> m_drawables;
    public:
        enum MouseEvent {
            Click = 0, Hover
        };
        Layer(sf::RenderWindow *w);
        void addDrawable(Drawable *d);
        void handleMouseEvent(MouseEvent event, sf::Vector2i mousePos);
        virtual void render();
        ~Layer();
    };
}

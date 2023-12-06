#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Drawable.hpp"

namespace Utils
{
    class Layer
    {
    private:
        std::vector<Drawable *> m_drawables;
    public:
        static enum MouseEvent {
            Click = 0, Hover
        };
        Layer();
        void addDrawable(Drawable *d);
        void handleMouseEvent(MouseEvent event, sf::Vector2i mousePos);
        virtual void render();
        ~Layer();
    };
}

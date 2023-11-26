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
        Layer();
        void addDrawable(Drawable *d);
        void handleClick(sf::Vector2i mousePos);
        virtual void render();
        ~Layer();
    };
}

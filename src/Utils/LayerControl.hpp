#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

#include "Layer.hpp"

namespace Utils
{
    class LayerControl
    {
    private:
        sf::RenderWindow *m_window;
        std::vector<Utils::Layer *> m_layers;
        Layer *m_topLayer;
    public:
        LayerControl(sf::RenderWindow *w);
        void addTop(Utils::Layer *l);
        void removeTop(Utils::Layer *l);
        Layer *top();
        void handleClick(sf::Vector2i mousePos);
        void render();
    };
}

#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

#include "Layer.hpp"

namespace Utils
{
    class LayerControl
    {
    private:
        std::vector<Utils::Layer *> m_layers;
        Layer *m_topLayer;
    public:
        LayerControl();
        void addTop(Utils::Layer *l);
        void remove(Utils::Layer *l);
        Layer *top();
        void handleClick(sf::Vector2i mousePos);
        void handleMouseMove(sf::Vector2i mousePos);
        void render();
    };
}

#include <algorithm>
#include "LayerControl.hpp"

Utils::LayerControl::LayerControl(sf::RenderWindow *w) :
m_window(w)
{
}

void Utils::LayerControl::addTop(Layer *l)
{
    m_layers.push_back(l);
    m_topLayer = l;
}

void Utils::LayerControl::removeTop(Layer *l)
{
    m_layers.erase(std::remove(m_layers.begin(), m_layers.end(), l));
    m_topLayer = m_layers.back();
}

Utils::Layer *Utils::LayerControl::top()
{
    return m_topLayer;
}

void Utils::LayerControl::handleClick(sf::Vector2i mousePos)
{
    m_topLayer->handleClick(mousePos);
}

void Utils::LayerControl::render()
{
    for (Layer *l : m_layers)
        l->render();
}

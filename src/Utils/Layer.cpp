#include "Layer.hpp"
Utils::Layer::Layer()
{
}

void Utils::Layer::addDrawable(Drawable *d)
{
    m_drawables.push_back(d);
}

void Utils::Layer::handleClick(sf::Vector2i mousePos)
{
    for (Drawable *d : m_drawables)
        if (d->isInArea(mousePos))
        {
            std::vector<Clickable *> clickables = d->getClickables();
            for (Clickable *c: clickables)
            {
                if (c->isInArea(mousePos))
                {
                    c->handleClick();
                    break;
                }   
            }
            break;
        }
}

void Utils::Layer::render()
{
    for (Drawable *d: m_drawables)
        d->render();
}

Utils::Layer::~Layer()
{
    for (Drawable *d : m_drawables)
        delete(d);
}

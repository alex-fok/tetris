#include "Layer.hpp"

Utils::Layer::Layer(sf::RenderWindow *w) :
m_window(w)
{
}

void Utils::Layer::addDrawable(Drawable *d)
{
    m_drawables.push_back(d);
}

void Utils::Layer::handleMouseEvent(Utils::Layer::MouseEvent event, sf::Vector2i mousePos)
{
    sf::Cursor cursor;
    for (Drawable *d : m_drawables)
    {
        if (!d->isInArea(mousePos))
            continue;
        
        Utils::Clickable **clickables = d->clickables;
        
        for (size_t i = 0; i < d->clickableCount; ++i)
        {
            if (clickables[i]->isInArea(mousePos))
            {
                if (cursor.loadFromSystem(sf::Cursor::Hand))
                    m_window->setMouseCursor(cursor);
            
                switch(event)
                {
                    case Click:
                        clickables[i]->handleClick();
                        break;
                    default:
                        clickables[i]->handleHover();
                        break;
                }
                break;
            }
            else if (cursor.loadFromSystem(sf::Cursor::Arrow))
                m_window->setMouseCursor(cursor);
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

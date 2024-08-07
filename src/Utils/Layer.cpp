#include "Layer.hpp"

Utils::Layer::Layer() :
    m_isEmpty(true)
{
}

Utils::Layer::Layer(sf::RenderWindow *w) :
    m_window(w),
    m_isEmpty(false)
{
}

void Utils::Layer::addDrawable(Drawable *d)
{
    if (m_isEmpty) return;
    m_drawables.push_back(d);
}

void Utils::Layer::handleMouseEvent(Utils::Layer::MouseEvent event, sf::Vector2i mousePos)
{
    sf::Cursor cursor;
    for (Drawable *d : m_drawables)
    {
        if (!d->isInArea(mousePos))
            continue;
        
        Utils::Drawable **drawables = d->drawables;
        
        for (size_t i = 0; i < d->drawableCount; ++i)
        {
            if (drawables[i]->isInArea(mousePos))
            {
                if (cursor.loadFromSystem(sf::Cursor::Hand))
                    m_window->setMouseCursor(cursor);
            
                switch(event)
                {
                    case Click:
                        drawables[i]->handleClick();
                        break;
                    default:
                        drawables[i]->handleHover();
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

#include "Drawable.hpp"

Utils::Drawable::Drawable()
{
}

Utils::Drawable::Drawable(sf::RenderWindow *w) :
m_window(w),
clickableCount(-1)
{
}

void Utils::Drawable::setClickables(Clickable **c, int size)
{
    clickables = c;
    clickableCount = size;
}

Utils::Clickable ** Utils::Drawable::getClickables()
{
    return clickables;
};

void Utils::Drawable::draw(const sf::Drawable &d)
{
    m_window->draw(d);
}

void Utils::Drawable::render()
{
}

Utils::Drawable::~Drawable()
{
    if (clickableCount <= 0) return;
    
    for (unsigned i = 0; i < clickableCount; ++i)
        delete clickables[i];
    
    delete [] clickables;
}

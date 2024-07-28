#include "Drawable.hpp"
#include <array>
#include <iostream>
#include <cmath>

Utils::Drawable::Drawable() :
drawableCount(0)
{
}

Utils::Drawable::Drawable(sf::RenderWindow *w) :
m_window(w),
drawableCount(0)
{
}

sf::Text Utils::Drawable::getDrawable()
{
    return m_content;
}

void Utils::Drawable::setPosition(sf::Vector2f position)
{
};

sf::Vector2f Utils::Drawable::getPosition()
{
    return m_content.getPosition();
}

void Utils::Drawable::setDrawables(Drawable **d, int size)
{
    drawables = d;
    drawableCount = size;
};

void Utils::Drawable::clearDrawables()
{
    if (drawables == NULL || drawableCount <= 0)
        return;
    for (size_t i = 0; i < drawableCount; ++i) {
        delete drawables[i];
    }
    drawableCount = 0;
    delete [] drawables;
}

void Utils::Drawable::draw(const sf::Drawable &d)
{
    m_window->draw(d);
}

void Utils::Drawable::handleClick()
{
}

void Utils::Drawable::handleHover()
{
}

void Utils::Drawable::render()
{
}

Utils::Drawable::~Drawable()
{
    if (drawableCount <= 0) return;
    
    for (size_t i = 0; i < drawableCount; ++i)
        delete drawables[i];
    
    drawableCount = 0;
    delete [] drawables;
}

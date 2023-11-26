#include "Drawable.hpp"

Utils::Drawable::Drawable(sf::RenderWindow *w) :
m_window(w)
{
}

void Utils::Drawable::addClickable(Clickable *c)
{
    m_clickables.push_back(c);
}

std::vector<Utils::Clickable *> Utils::Drawable::getClickables()
{
    return m_clickables;
};

void Utils::Drawable::draw(const sf::Drawable &d)
{
    m_window->draw(d);
}

void Utils::Drawable::render()
{
}

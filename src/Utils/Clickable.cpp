#include "Clickable.hpp"
Utils::Clickable::Clickable()
{
}

void Utils::Clickable::handleClick()
{
    // Handle click event
    m_fn();
}

void Utils::Clickable::setPosition(sf::Vector2f position)
{
}

sf::Text Utils::Clickable::getClickable()
{
    return m_content;
}

void Utils::Clickable::setFn(std::function<void()> fn)
{
    m_fn = fn;
}

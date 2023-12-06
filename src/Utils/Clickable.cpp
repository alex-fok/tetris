#include "Clickable.hpp"
Utils::Clickable::Clickable()
{
}

void Utils::Clickable::setPosition(sf::Vector2f position)
{
}

sf::Text Utils::Clickable::getClickable()
{
    return m_content;
}

void Utils::Clickable::handleClick()
{
    m_click_fn();
}

void Utils::Clickable::handleHover()
{
    m_hover_fn();
}

void Utils::Clickable::setClickFn(std::function<void()> fn)
{
    m_click_fn = fn;
}

void Utils::Clickable::setHoverFn(std::function<void()> fn)
{
    m_hover_fn = fn;
}

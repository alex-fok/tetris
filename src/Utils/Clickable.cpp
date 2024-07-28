#include "Clickable.hpp"
#include <iostream>
Utils::Clickable::Clickable()
{
}

void Utils::Clickable::handleClick()
{
    m_click_fn();
}

void Utils::Clickable::handleHover()
{
    m_hover_fn();
}

void Utils::Clickable::render()
{
}

void Utils::Clickable::setClickFn(std::function<void()> fn)
{
    m_click_fn = fn;
}

void Utils::Clickable::setHoverFn(std::function<void()> fn)
{
    m_hover_fn = fn;
}

#include "Base.hpp"

Menu::Base::Base(sf::RenderWindow *w, sf::Vector2f v):
    m_window(w),
    m_container(v)
{
    m_container.setOrigin({v.x/2.f, v.y/2.f});
    m_container.setPosition({400.f, 300.f});
    m_container.setFillColor(sf::Color::Black);
    m_container.setOutlineColor(sf::Color::White);
    m_container.setOutlineThickness(-1.0f);
}

void Menu::Base::render()
{
    m_window->draw(m_container);
}

#include "Base.hpp"
#include "../GameUI/Config.hpp"

Menu::Base::Base(sf::RenderWindow *w, sf::Vector2f size, const char *title):
    m_window(w),
    m_container(size)
{
    float width_ctr = GameUI::Config::Window::Width / 2.f;
    float height_ctr = GameUI::Config::Window::Height / 2.f;
    
    // Container
    m_container.setOrigin({size.x/2.f, size.y/2.f});
    m_container.setPosition({width_ctr, height_ctr});
    m_container.setFillColor(sf::Color::Black);
    m_container.setOutlineColor(sf::Color::White);
    m_container.setOutlineThickness(-1.0f);

    // Title
    m_title.setString(title);
    m_title.setFont(fontCollection.RobotoRegular);
    sf::FloatRect bounds = m_title.getLocalBounds();
    m_title.setOrigin({bounds.width / 2, bounds.height / 2});
    m_title.setPosition({width_ctr, size.y * 0.1f  + (height_ctr - size.y/2.f)});
}

void Menu::Base::renderBase()
{
    m_window->draw(m_container);
    m_window->draw(m_title);
}

void Menu::Base::render()
{
    renderBase();
}

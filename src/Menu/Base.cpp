#include "Base.hpp"
#include "../GameUI/Config.hpp"

Menu::Base::Base(sf::RenderWindow *w, sf::Vector2f size, const char *title):
    Drawable(w),
    fontCollection(Resources::FontCollection::getInstance()),
    m_size(size),
    m_offset({
        GameUI::Config::Window::Height/2.f - size.y/2.f, // Top
        GameUI::Config::Window::Width/2.f + size.x/2.f, // Right
        GameUI::Config::Window::Height/2.f + size.y/2.f, // Bottom
        GameUI::Config::Window::Width/2.f - size.x/2.f // Left
    }),
    m_container(sf::RectangleShape(size))
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
    m_title.setFont(fontCollection->RobotoRegular);
    m_title.setCharacterSize(36);
    sf::FloatRect bounds = m_title.getLocalBounds();
    m_title.setOrigin({bounds.width / 2, bounds.height / 2});
    m_title.setPosition({width_ctr, m_size.y * 0.1f + m_offset.top});
}

void Menu::Base::setButtonPositions(std::vector<Utils::Button *> btns)
{
    std::size_t size = btns.size();
    float start = ceil(5.f + (5.f - float(size)) / 2.f);
    float x = m_container.getPosition().x; // centered
    
    for (std::size_t i = 0; i < size; ++i)
        btns[i]->setPosition({x, m_size.y * 0.1f * (i + start) + m_offset.top});
}

void Menu::Base::renderBase()
{
    draw(m_container);
    draw(m_title);
}

void Menu::Base::render()
{
    renderBase();
}

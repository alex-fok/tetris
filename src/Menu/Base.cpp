#include "Base.hpp"
#include "../GameUI/Config.hpp"

Menu::Base::Base(sf::RenderWindow *w) :
    Drawable(w),
    fontCollection(Resources::FontCollection::getInstance())
{
}

void Menu::Base::setup(float width, float height, const char *title)
{
    m_offset = {
        GameUI::Config::Window::Height/2.f - height/2.f, // Top
        GameUI::Config::Window::Width/2.f + width/2.f, // Right
        GameUI::Config::Window::Height/2.f + height/2.f, // Bottom
        GameUI::Config::Window::Width/2.f - width/2.f // Left
    };

    m_container = sf::RectangleShape({width, height});

    float window_width_ctr = GameUI::Config::Window::Width / 2.f;
    float window_height_ctr = GameUI::Config::Window::Height / 2.f;
    
    float container_width_ctr = width/2.f;
    float container_height_ctr = height/2.f;

    // Container
    m_container = sf::RectangleShape({width, height});
    m_container.setOrigin({container_width_ctr, container_height_ctr});
    m_container.setPosition({window_width_ctr, window_height_ctr});
    m_container.setFillColor(sf::Color::Black);
    m_container.setOutlineColor(sf::Color::White);
    m_container.setOutlineThickness(-1.0f);

    // Set Area/Position
    setArea(
        { window_width_ctr - container_width_ctr, window_height_ctr - container_height_ctr },
        { window_width_ctr + container_width_ctr, window_height_ctr + container_height_ctr }
    );

    // Title
    m_title.setString(title);
    m_title.setFont(fontCollection->RobotoRegular);
    m_title.setCharacterSize(36);
    sf::FloatRect bounds = m_title.getLocalBounds();
    m_title.setOrigin({bounds.width / 2, bounds.height / 2});
    m_title.setPosition({window_width_ctr, height * 0.1f + m_offset.top});
}

void Menu::Base::setButtonPositions()
{
    std::size_t size = m_clickables.size();
    float start = ceil(5.f + (5.f - float(size)) / 2.f);
    float x = m_container.getPosition().x; // centered
    
    for (std::size_t i = 0; i < size; ++i)
        m_clickables[i]->setPosition({x, height * 0.1f * (i + start) + m_offset.top});
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

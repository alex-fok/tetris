#include <cmath>
#include "Base.hpp"
#include "../GameUI/Config.hpp"

Menu::Base::Base(sf::RenderWindow *w) :
    Drawable(w),
    fontCollection(Resources::FontCollection::getInstance()),
    m_cursor(sf::CircleShape(7.5f, 3)),
    m_selected(-1)
{
    sf::FloatRect fr = m_cursor.getLocalBounds();
    m_cursor.setOrigin(fr.width/2, fr.height/2);
    m_cursor.rotate(90);
}

void Menu::Base::m_setup(float width, float height, const char *title)
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

void Menu::Base::m_setButtonPositions()
{
    float start = ceil(5.f + (5.f - float(clickableCount)) / 2.f);
    float x = m_container.getPosition().x; // centered
    
    for (std::size_t i = 0; i < clickableCount; ++i)
        clickables[i]->setPosition({x, m_height * 0.1f * (i + start) + m_offset.top});
}

void Menu::Base::setSelectedIdx(unsigned int idx)
{
    if (m_selected == idx)
        return;

    m_selected = idx;
    auto selectedBtn = (Utils::Button *)clickables[idx];
    auto fr = m_cursor.getLocalBounds();
    auto selected_pos = selectedBtn->getPosition();
    m_cursor.setPosition(selected_pos.x - selectedBtn->m_width - fr.width/2, selected_pos.y);
}

void Menu::Base::handle(sf::Keyboard::Key input)
{
    switch(input)
    {
        case sf::Keyboard::Up:
            setSelectedIdx(std::max(m_selected - 1, 0));
            break;
        case sf::Keyboard::Down:
            setSelectedIdx(std::min(m_selected + 1, clickableCount - 1));
            break;
        case sf::Keyboard::Enter:
            clickables[m_selected]->handleClick();
            break;
        default:
            break;
    }
}

void Menu::Base::m_renderBase()
{
    draw(m_container);
    draw(m_title);
    draw(m_cursor);
}

void Menu::Base::render()
{
    m_renderBase();
    for (size_t i = 0; i < clickableCount; ++i)
        draw(clickables[i]->getClickable());
}

void Menu::Base::forwarder_setSelected(Menu::Base *self, unsigned int idx)
{
    self->setSelectedIdx(idx);
}

#include "Button.hpp"
#include <iostream>

Utils::Button::Button(const char *name, Resources::FontCollection *fc)
{
    m_content.setString(name);
    m_content.setFont(fc->RobotoRegular);
    m_content.setCharacterSize(18);
    sf::FloatRect bounds = m_content.getLocalBounds();
    m_width = bounds.width;
    m_height = bounds.height;
    m_content.setOrigin({bounds.width / 2, bounds.height / 2});
}

void Utils::Button::setPosition(sf::Vector2f position)
{
   m_content.setPosition(position);
   setArea(
    { position.x - m_width/2.f, position.y - m_width/2.f },
    { position.x + m_width/2.f, position.y + m_width/2.f }
   );
}

void Utils::Button::render()
{
    draw(m_content);
}

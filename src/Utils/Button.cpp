#include "Button.hpp"

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

sf::Vector2f Utils::Button::getPosition()
{
    return m_content.getPosition();
}

#include "Button.hpp"

Utils::Button::Button(const char *name, Resources::FontCollection *fc)
{
    content.setString(name);
    content.setFont(fc->RobotoRegular);
    content.setCharacterSize(18);
    sf::FloatRect bounds = content.getLocalBounds();
    content.setOrigin({bounds.width / 2, bounds.height / 2});
}

void Utils::Button::setPosition(sf::Vector2f position)
{
    content.setPosition(position);
}

sf::Text const Utils::Button::getButton()
{
    return content;
}

void Utils::Button::setFn(void (* fn)())
{
    m_fn = fn;
}

void Utils::Button::handleClick()
{
    m_fn();
}

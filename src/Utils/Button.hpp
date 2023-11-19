#pragma once
#include <SFML/Graphics.hpp>
#include "../Resources/FontCollection.hpp"

namespace Utils
{
    class Button
    {
    private:
        void (*m_fn)();
    public:
        sf::Text content;
        Button(const char *name, Resources::FontCollection *fc);
        void setPosition(sf::Vector2f position);
        sf::Text const getButton();
        void setFn(void (*fn)());
        void handleClick();
    };
}

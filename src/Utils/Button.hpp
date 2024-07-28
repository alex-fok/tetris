#pragma once
#include <SFML/Graphics.hpp>
#include "Clickable.hpp"
#include "../Resources/FontCollection.hpp"

namespace Utils
{
    class Button : public Clickable
    {
    public:
        Button(const char *name, Resources::FontCollection *fc);
        sf::Text *getContent();
        void setPosition(sf::Vector2f position);
        sf::Vector2f getPosition();
        virtual void render();
    };
}

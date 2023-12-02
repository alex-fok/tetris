#pragma once
#include <functional>
#include <SFML/Graphics.hpp>
#include "Area.hpp"

namespace Utils
{
    class Clickable : public Area
    {
    private:
        std::function<void()> m_fn;
    protected:
        sf::Text m_content;
    public:
        Clickable();
        virtual void setPosition(sf::Vector2f position);
        sf::Text getClickable();
        void setFn(std::function<void()> fn);
        virtual void handleClick();
    };
}

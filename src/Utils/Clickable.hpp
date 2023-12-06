#pragma once
#include <functional>
#include <SFML/Graphics.hpp>
#include "Area.hpp"

namespace Utils
{
    class Clickable : public Area
    {
    private:
        std::function<void()> m_click_fn;
        std::function<void()> m_hover_fn;
    protected:
        sf::Text m_content;
    public:
        Clickable();
        virtual void setPosition(sf::Vector2f position);
        sf::Text getClickable();
        
        void handleClick();
        void handleHover();
        void setClickFn(std::function<void()> fn);
        void setHoverFn(std::function<void()> fn);
    };
}

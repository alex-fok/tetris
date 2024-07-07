#pragma once
#include <functional>
#include <SFML/Graphics.hpp>
#include "Drawable.hpp"
#include "Area.hpp"

namespace Utils
{
    class Clickable : public Drawable
    {
    private:
        std::function<void()> m_click_fn;
        std::function<void()> m_hover_fn;
    public:
        Clickable();
        sf::Text getClickable();
        
        void handleClick();
        void handleHover();
        void setClickFn(std::function<void()> fn);
        void setHoverFn(std::function<void()> fn);
    };
}

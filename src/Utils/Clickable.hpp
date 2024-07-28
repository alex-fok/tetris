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
        void handleClick();
        void handleHover();
        virtual void render();
        void setClickFn(std::function<void()> fn);
        void setHoverFn(std::function<void()> fn);
    };
}

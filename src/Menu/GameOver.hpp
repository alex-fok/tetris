#pragma once
#include <functional>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../GameUI/Config.hpp"
#include "../Utils/Button.hpp"
#include "Base.hpp"

namespace Menu
{
    class GameOver : public Base
    {
    private:
        std::function<void()> m_resetFn;
    public:
        GameOver(sf::RenderWindow *w, std::function<void()> retryFn);
        void render();
    };
}

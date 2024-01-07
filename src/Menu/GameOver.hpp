#pragma once
#include <functional>
#include <SFML/Graphics.hpp>
#include "../GameUI/Config.hpp"
#include "../Utils/Button.hpp"
#include "Base.hpp"

namespace Menu
{
    class GameOver : public Base
    {
    private:
        std::function<void()> m_retryFn;
        std::function<void()> m_quitFn;
    public:
        GameOver(sf::RenderWindow *w, std::function<void()> retryFn, std::function<void()> quitFn);
        void handle(sf::Keyboard::Key input);
    };
}

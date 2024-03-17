#pragma once
#include "SFML/Graphics.hpp"
#include "../GameUI/Config.hpp"
#include "Base.hpp"

namespace Menu
{
    class Start : public Base
    {
    private:
        std::function<void()> m_startGameFn;
        std::function<void()> m_quitFn;
    public:
        Start(sf::RenderWindow *w, std::function<void()> startGameFn, std::function<void()> quitFn);
        void handle(sf::Keyboard::Key input);
    };
}

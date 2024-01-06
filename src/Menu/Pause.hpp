#pragma once
#include <functional>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../GameUI/Config.hpp"
#include "Base.hpp"

namespace Menu
{
    class Pause : public Base
    {
    private:
        std::function<void()> m_resumeFn;
    public:
        Pause(sf::RenderWindow *w, std::function<void()> resumeFn);
        void handle(sf::Keyboard::Key input);
    };
}

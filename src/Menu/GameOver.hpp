#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "../GameUI/Config.hpp"
#include "../Utils/Button.hpp"
#include "Base.hpp"

namespace Menu
{
    class GameOver : public Base
    {
    public:
        GameOver(sf::RenderWindow *w);
        void retry();
        void render();
    };
}

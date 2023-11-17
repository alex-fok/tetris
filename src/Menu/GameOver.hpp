#pragma once
#include <SFML/Graphics.hpp>
#include "Base.hpp"

namespace Menu
{
    class GameOver : public Base
    {
    private:
        static constexpr float s_Width = 250.f;
        static constexpr float s_Height = 400.f;
        
    public:
        GameOver(sf::RenderWindow *w);
        void render();
    };
}

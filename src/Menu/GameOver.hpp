#pragma once
#include <SFML/Graphics.hpp>
#include "Base.hpp"
namespace Menu
{
    class GameOver : public Base
    {
    private:
        static constexpr float Width = 250.f;
        static constexpr float Height = 400.f;
    public:
        GameOver(sf::RenderWindow *w);
    };
}

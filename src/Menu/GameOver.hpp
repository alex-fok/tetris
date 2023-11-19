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
    private:
        static constexpr float s_Width = GameUI::Config::Menu::GameOver::Width;
        static constexpr float s_Height = GameUI::Config::Menu::GameOver::Height;
        std::vector<Utils::Button *> m_buttons;
        
    public:
        GameOver(sf::RenderWindow *w);
        void retry();
        void render();
    };
}

#pragma once
#include <SFML/Graphics.hpp>
#include "../Utils/LayerControl.hpp"
#include "../Utils/Layer.hpp"
#include "../GameEntity/TetrominoContainer.hpp"
#include "../Menu/GameOver.hpp"

namespace GameUI
{
    class UI
    {
    private:
        sf::RenderWindow m_window;
        Status m_status;
        Utils::LayerControl m_layerControl;
        GameEntity::TetrominoContainer m_tetroContainer;
        Menu::GameOver m_gameOverMenu;
        void retry();
        void setGameOver();
        void setPaused();
        void setRunning();
        
        static void forwarder_setStatus(GameUI::UI *, Status s);
        static void forwarder_retry(GameUI::UI *);
    public:
        UI();
        void run();
        void setStatus(Status s);
    };
}

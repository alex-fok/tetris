#pragma once
#include <SFML/Graphics.hpp>
#include "../Utils/LayerControl.hpp"
#include "../Utils/Layer.hpp"
#include "../GameEntity/TetrominoFactory.hpp"
#include "../GameEntity/PreviewList.hpp"
#include "../GameEntity/TetrominoContainer.hpp"
#include "../Menu/GameOver.hpp"
#include "../Menu/Pause.hpp"

namespace GameUI
{
    class UI
    {
    private:
        sf::RenderWindow m_window;
        Status m_status;
        Utils::LayerControl m_layerControl;
        GameEntity::TetrominoFactory m_tetroFactory;
        GameEntity::PreviewList m_previewList;
        GameEntity::TetrominoContainer m_tetroContainer;
        Menu::GameOver m_gameOverMenu;
        Menu::Pause m_pauseMenu;
        
        void retry();
        void close();
        void setGameOver();
        void setPaused();
        void setRunning();
        
        static void forwarder_setStatus(GameUI::UI *, Status s);
        static void forwarder_retry(GameUI::UI *);
        static void forwarder_close(GameUI::UI *);
    public:
        UI();
        void run();
        void setStatus(Status s);
    };
}

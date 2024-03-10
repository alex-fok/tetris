#pragma once
#include <SFML/Graphics.hpp>
#include "../Utils/LayerControl.hpp"
#include "../Utils/Layer.hpp"
#include "../GameAnimation/Scoring.hpp"
#include "../GameAnimation/ClearLines.hpp"
#include "../GameEntity/TetrominoFactory.hpp"
#include "../GameEntity/ScoreAction.hpp"
#include "../GameEntity/ScoringSystem.hpp"
#include "../GameEntity/Score.hpp"
#include "../GameEntity/PreviewList.hpp"
#include "../GameEntity/Hold.hpp"
#include "../GameEntity/TetrominoContainer.hpp"
#include "../Menu/GameOver.hpp"
#include "../Menu/Pause.hpp"
#include "Status.hpp"

namespace GameUI
{
    class UI
    {
    private:
        sf::RenderWindow m_window;
        Status m_status;
        Status m_status_before_animation;
        Utils::LayerControl m_layerControl;
        GameAnimation::Scoring m_scoreAnimation;
        GameAnimation::ClearLines m_clearLinesAnimation;
        GameEntity::TetrominoFactory m_tetroFactory;
        GameEntity::ScoringSystem m_scoringSystem;
        GameEntity::Score m_score;
        GameEntity::PreviewList m_previewList;
        GameEntity::Hold m_hold;
        GameEntity::TetrominoContainer m_tetroContainer;
        Menu::GameOver m_gameOverMenu;
        Menu::Pause m_pauseMenu;
        
        void retry();
        void close();
        void setGameOver();
        void setPaused();
        void setRunning();
        void setStatus(Status s);
        void startAnimation();
        void stopAnimation();
        static void forwarder_setStatus(GameUI::UI *, Status s);
        static void forwarder_startAnimation(GameUI::UI *);
        static void forwarder_stopAnimation(GameUI::UI *);
        static void forwarder_retry(GameUI::UI *);
        static void forwarder_close(GameUI::UI *);
    public:
        UI();
        void run();
    };
}

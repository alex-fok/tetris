#pragma once
#include <functional>
#include <SFML/Graphics.hpp>
#include "../Utils/Drawable.hpp"
#include "../GameUI/Config.hpp"
#include "../GameUI/Status.hpp"
#include "../GameSetting/Setting.hpp"
#include "../GameAnimation/ClearLines.hpp"
#include "Vector.hpp"
#include "Block.hpp"
#include "ScoreAction.hpp"
#include "ScoringSystem.hpp"
#include "ActiveTetromino.hpp"
#include "Tetromino.hpp"
#include "TetrominoFactory.hpp"

namespace GameEntity
{
    class TetrominoContainer : public Utils::Drawable
    {
    private:
        static constexpr GameUI::Count m_blockCount = GameUI::Config::TetrominoContainer::BlockCount;
        static constexpr GameUI::Count m_initPos = { 3, m_blockCount.y - ActiveTetromino::Offset_size };
        
        std::vector<int> m_linesToClear;
        
        float m_blockSize, m_borderWidth;

        sf::RenderWindow *m_window;
        sf::RectangleShape m_frame;

        TetrominoFactory *m_tetrominoFactory;
        ActiveTetromino m_active;
        Block m_arr[m_blockCount.y + GameUI::Config::TetrominoContainer::HiddenLines][m_blockCount.x];
        ScoringSystem *m_scoringSystem;
        GameSetting::Setting *m_setting;
        GameAnimation::ClearLines *m_clearLinesAnimation;
        std::function<Tetromino *(Tetromino *)> m_setHold;
        std::function<void(GameUI::Status)> m_setStatus;
    public:
        TetrominoContainer(
            sf::RenderWindow *w,
            TetrominoFactory *tetroFactory,
            ScoringSystem *scoringSystem,
            GameSetting::Setting *setting,
            GameAnimation::ClearLines *m_clearLinesAnimation,
            std::function<Tetromino *(Tetromino *)>setHold,
            std::function<void(GameUI::Status)> statusSetter
        );
        void nextStep();
        void handle(sf::Keyboard::Key);
        void reset();
        void render();
        ~TetrominoContainer();

    private:
        bool isBlocked(Vector v);
        void rotate(Tetromino::RotateDirection);
        void move(Vector v);
        void softDrop();
        void hardDrop();
        void clearLines();
        Vector getStartPos(Tetromino *t);
        bool isGameOver();
        void scoreOrContinue();
        void placeNewActive();
        void settleActive();
        void updateActive(bool isUpdateTimer);
        void clearActive();
        void switchTetro();
        void drawBlocks();
    };
};

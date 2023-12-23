#pragma once
#include <functional>
#include <SFML/Graphics.hpp>
#include "../Utils/Drawable.hpp"
#include "../GameUI/Config.hpp"
#include "../GameUI/Status.hpp"
#include "Vector.hpp"
#include "Block.hpp"
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
        
        std::vector<int> linesToClear;
        
        float m_blockSize, m_borderWidth;

        sf::RenderWindow *m_window;
        sf::RectangleShape m_frame;

        TetrominoFactory *m_tetrominoFactory;
        ActiveTetromino m_active;
        Block m_arr[m_blockCount.y + ActiveTetromino::Offset_size][m_blockCount.x];
        std::function<void(GameUI::Status)> m_setStatus;
    public:
        TetrominoContainer(
            sf::RenderWindow *w,
            TetrominoFactory *tetroFactory,
            std::function<void(GameUI::Status)> statusSetter
        );        
        void nextStep();
        void handle(sf::Keyboard::Key);
        void reset();
        void render();
        ~TetrominoContainer();

    private:
        bool isBlocked(Vector v);
        void rotate(Tetromino::Rotation);
        void move(Vector v);
        void drop();
        void clearLines();
        void placeNewActive();
        void settleActive();
        void updateActive();
        void clearActive();
        
        void drawBlocks();
    };
};

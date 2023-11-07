#pragma once
#include <SFML/Graphics.hpp>
#include "Vector.hpp"
#include "Block.hpp"
#include "ActiveTetromino.hpp"
#include "Tetromino.hpp"
#include "TetrominoFactory.hpp"

namespace GameEntity
{
    class TetrominoContainer
    {
    private:
        static const int BlockCount_x = 10;
        static const int BlockCount_y = 20;
        static const int InitPos_x = 3;
        static const int InitPos_y = BlockCount_y - ActiveTetromino::Offset_size;
        std::vector<int> linesToClear;

        float m_blockSize, m_borderWidth;
        float m_pos_x, m_pos_y;

        sf::RenderWindow *m_window;
        sf::RectangleShape m_frame;

        TetrominoFactory m_tetrominoFactory;
        ActiveTetromino m_active;
        Block m_arr[BlockCount_y][BlockCount_x];

    public:
        TetrominoContainer(sf::RenderWindow *w, float blockSize, float borderWidth, float pos_x, float pos_y);
        bool nextStep();
        void handle(sf::Keyboard::Key);
        void render();
        ~TetrominoContainer();

    private:
        bool isBlocked(Vector v);
        void rotate(Tetromino::Rotation);
        void move(Vector v);
        void drop();
        void clearLines();
        void settleActive();        
        void updateActive();
        void clearActive();
        
        void drawBlocks();
    };
};

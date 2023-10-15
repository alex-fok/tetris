#pragma once
#include <SFML/Graphics.hpp>
#include "Vector.hpp"
#include "Block.hpp"
#include "TetrominoFactory.hpp"
namespace GameEntity
{
    struct ActiveTetromino
    {
        static const int Offset_size = 4;
        GameEntity::Tetromino *tetromino;
        // offset[] = {x, y}
        Vector offset;
    };

    class TetrominoContainer
    {
    private:
        static const int INIT_POS_X = 3;
        static const int INIT_POS_Y = 0;
        static const int m_blockCount_x = 10;
        static const int m_blockCount_y = 20;

        float m_blockSize, m_borderWidth;
        float m_pos_x, m_pos_y;

        sf::RenderWindow *m_window;
        sf::RectangleShape m_container;

        TetrominoFactory m_tetrominoFactory;
        ActiveTetromino m_active;
        Block m_arr[m_blockCount_y][m_blockCount_x];

    public:
        TetrominoContainer(sf::RenderWindow *window, float blockSize, float borderWidth, float pos_x, float pos_y);
        void moveRight();
        void moveLeft();
        void moveDown();
        void drop();
        void rotateTetromino();
        void nextActive();
        void render();
        ~TetrominoContainer();

    private:
        void placeActive(Vector, Direction);
        void clearActive();
        
        void drawBlocks();
        void drawContent();
    };
};

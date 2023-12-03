#pragma once
#include "Tetromino.hpp"

namespace GameEntity
{
    class TetrominoFactory
    {
    private:
        unsigned short m_currIdx;
    public:
        TetrominoFactory();
        Tetromino *generateTetromino();
        void reset();
    };
}

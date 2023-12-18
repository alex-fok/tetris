#pragma once
#include <algorithm>
#include <deque>
#include "Tetromino.hpp"

namespace GameEntity
{
    class TetrominoFactory
    {
    private:
        static const size_t m_tetro_size = 4;
        std::deque<Tetromino *> m_tetros;
        unsigned short m_currIdx;
    public:
        TetrominoFactory();
        Tetromino *getNext();
        void reset();
    };
}

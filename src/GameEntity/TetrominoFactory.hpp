#pragma once
#include <algorithm>
#include <deque>
#include "Tetromino.hpp"

namespace GameEntity
{
    class TetrominoFactory
    {
    private:
        static const size_t m_tetro_size = 14;
        static const size_t m_bag_size = 7;
        std::deque<Tetromino *> m_tetros;
        unsigned short m_currIdx;
        void init();
        void addTetros(int *bag);
        int *getBag();
    public:
        TetrominoFactory();
        Tetromino *getNext();
        void reset();
    };
}

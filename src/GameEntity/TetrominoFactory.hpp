#pragma once
#include <functional>
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
        std::vector<std::function<void()>> m_subscribed_fns;
        unsigned short m_currIdx;
        void init();
        void addTetros(int *bag);
        int *getBag();
    public:
        TetrominoFactory();
        void peek(size_t count, Tetromino **array);
        Tetromino *getNext();
        void reset();
        void addSubscription(std::function<void()> fn);
    };
}

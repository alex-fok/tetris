#pragma once
#include "Tetromino.hpp"

namespace GameEntity
{
    class ActiveTetromino
    {
    public:
    enum ActiveStat {
        Active = 0, CountDown, Settled
    };
    public:
        static const int Offset_size = 4;
        GameEntity::Tetromino *tetromino;
        Vector offset;
        int ghost_y;
        static const sf::Int32 SettleTimeLimit = 1000;
        static const sf::Int32 DownTimeLimit = 800;
        sf::Clock elapsed;
        ActiveStat stat;
        ActiveTetromino(GameEntity::Tetromino *tetromino, Vector offset);
        void updateStat(ActiveStat a);
        bool isSettled();
        bool shouldSettle();
        bool shouldDrop();
    };
}

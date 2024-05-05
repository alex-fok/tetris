#pragma once
#include "Vector.hpp"
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
        bool isRotated;
        bool isSwitched;
        
        unsigned int wallkickOffset;
        int ghost_y;
        static const sf::Int32 SettleTimeLimit = 1000;
        static const sf::Int32 DownTimeLimit = 800;
        sf::Clock elapsed;
        ActiveStat stat;
        ActiveTetromino(GameEntity::Tetromino *tetromino, Vector offseta, bool isSwitched = false);
        void updateStat(ActiveStat a, bool isResetTimer);
        
        bool isSettled();
        bool shouldSettle();
        bool shouldDrop();
    };
}

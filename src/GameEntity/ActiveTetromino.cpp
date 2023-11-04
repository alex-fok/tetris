#include "ActiveTetromino.hpp"

void GameEntity::ActiveTetromino::updateStat(ActiveStat s)
{
    elapsed.restart();
    stat = s;
}

bool GameEntity::ActiveTetromino::isSettled()
{
    return stat == Settled;
}

bool GameEntity::ActiveTetromino::shouldSettle()
{
    return stat == CountDown && elapsed.getElapsedTime().asMilliseconds() > GameEntity::ActiveTetromino::SettleTimeLimit;
}

bool GameEntity::ActiveTetromino::shouldDrop()
{
    return stat == Active && elapsed.getElapsedTime().asMilliseconds() > GameEntity::ActiveTetromino::DownTimeLimit;
}

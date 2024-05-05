#include "ActiveTetromino.hpp"

GameEntity::ActiveTetromino::ActiveTetromino(GameEntity::Tetromino *tetromino, Vector offset, bool isSwitched):
tetromino(tetromino),
offset(offset),
isSwitched(isSwitched)
{
}
void GameEntity::ActiveTetromino::updateStat(ActiveStat s, bool isResetTimer)
{
    if (isResetTimer)
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

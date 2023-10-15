#include "Tetromino.hpp"

GameEntity::Tetromino::Tetromino(int i, GameEntity::BlockType type) :
    m_rotation(0), type(type), id(i), blockPosition(TetrominoType[type][0])
{
}

const GameEntity::Vector * GameEntity::Tetromino::peek()
{
    return TetrominoType[type][(m_rotation + 1) % 4];
}

void GameEntity::Tetromino::rotate(Direction dir)
{
    if (dir == Direction::Clockwise)
        blockPosition = TetrominoType[type][++m_rotation % 4];
    else if (dir == Direction::CounterClockwise)
        blockPosition = TetrominoType[type][--m_rotation % 4];
}

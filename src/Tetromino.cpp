#include "Tetromino.hpp"

GameEntity::Tetromino::Tetromino(int i, GameEntity::BlockType type) :
    m_rotation(0), type(type), id(i), position(TetrominoType[type][0])
{
}

const GameEntity::Vector * GameEntity::Tetromino::peek()
{
    return TetrominoType[type][(m_rotation + 1) % 4];
}

void GameEntity::Tetromino::rotate(Rotation dir)
{
    if (dir == Rotation::Clockwise)
        position = TetrominoType[type][++m_rotation % 4];
    else if (dir == Rotation::CounterClockwise)
        position = TetrominoType[type][--m_rotation % 4];
}

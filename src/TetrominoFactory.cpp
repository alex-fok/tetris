#include <stdlib.h>
#include <time.h>
#include "TetrominoFactory.hpp"

GameEntity::TetrominoFactory::TetrominoFactory() :
    m_currIdx(0)
{
    srand((unsigned int)time(NULL));
}

GameEntity::Tetromino * GameEntity::TetrominoFactory::generateTetromino()
{
    GameEntity::BlockType type = GameEntity::BlockType(rand() % 7);
    // GameEntity::BlockType type = GameEntity::BlockType(I);
    m_currIdx = (m_currIdx + 1) % 4;
    return new Tetromino(m_currIdx, type);
}

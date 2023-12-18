#include <stdlib.h>
#include <time.h>
#include "TetrominoFactory.hpp"

GameEntity::TetrominoFactory::TetrominoFactory() :
    m_currIdx(0)
{
    for (size_t i = 0; i < m_tetro_size; ++i)
        m_tetros.push_back(new Tetromino(m_currIdx + i, GameEntity::BlockType(rand() % 7)));

    m_currIdx += m_tetro_size;
    srand((unsigned int)time(NULL));
}

GameEntity::Tetromino * GameEntity::TetrominoFactory::getNext()
{
    Tetromino *front = m_tetros.front();
    m_tetros.pop_front();
    m_tetros.push_back(new Tetromino(m_currIdx, GameEntity::BlockType(rand() % 7)));
    
    m_currIdx = (m_currIdx + 1) % 256;
    return front;
}

void GameEntity::TetrominoFactory::reset()
{   
    for (auto tetro_ptr : m_tetros)
        delete(tetro_ptr);
    
    m_tetros.clear();
    m_currIdx = 0;

    for (size_t i = 0; i < m_tetro_size; ++i)
        m_tetros.push_back(new Tetromino(m_currIdx + i, GameEntity::BlockType(rand() % 7)));

    m_currIdx += m_tetro_size;
}

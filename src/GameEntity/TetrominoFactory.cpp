#include <stdlib.h>
#include <time.h>
#include "TetrominoFactory.hpp"

GameEntity::TetrominoFactory::TetrominoFactory() :
    m_currIdx(0)
{
    srand((unsigned int)time(NULL));
    init();
}

void GameEntity::TetrominoFactory::init()
{
    int *first_bag = getBag();
    while (
        first_bag[0] == GameEntity::BlockType::O ||
        first_bag[0] == GameEntity::BlockType::S ||
        first_bag[0] == GameEntity::BlockType::Z
    ) {
        delete(first_bag);
        first_bag = getBag();
    }
    addTetros(first_bag); // First
    addTetros(getBag()); // Second
}

void GameEntity::TetrominoFactory::addTetros(int *bag)
{
    for (size_t i = 0; i < m_bag_size; ++i)
        m_tetros.push_back(new Tetromino(m_currIdx++ % 256, GameEntity::BlockType(bag[i]))); 

    delete(bag);
}

int *GameEntity::TetrominoFactory::getBag()
{
    // Create Bag
    int *bag = new int[m_bag_size] {0, 1, 2, 3, 4, 5, 6};
    for (size_t i = 0; i < m_bag_size - 1; ++i)
    {
        int j = rand() % (m_bag_size - i) + i;
        std::swap(bag[i], bag[j]);
    }
    return bag;
}

void GameEntity::TetrominoFactory::peek(size_t count, Tetromino **array)
{
    size_t counter = 0;
    for (auto it = m_tetros.begin(); counter < count; ++it)
        array[counter++] = *it;
}

GameEntity::Tetromino * GameEntity::TetrominoFactory::getNext()
{
    Tetromino *front = m_tetros.front();
    m_tetros.pop_front();
    if (m_tetros.size() < m_bag_size + 1)
        addTetros(getBag());
    
    for (auto fn: m_subscribed_fns)
        fn();
    
    return front;
}

void GameEntity::TetrominoFactory::reset()
{   
    for (auto tetro_ptr : m_tetros)
        delete(tetro_ptr);
    
    m_tetros.clear();
    m_currIdx = 0;

    init();

    for (auto fn: m_subscribed_fns)
        fn();
}

void GameEntity::TetrominoFactory::addSubscription(std::function<void()> fn)
{
    m_subscribed_fns.push_back(fn);
}

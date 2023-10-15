#pragma once
#include "TetrominoContainer.hpp"
#include <iostream>

GameEntity::TetrominoContainer::TetrominoContainer(sf::RenderWindow *window, float blockSize, float borderWidth, float pos_x, float pos_y) :
    m_blockSize(blockSize), m_borderWidth(borderWidth),
    m_pos_x(pos_x), m_pos_y(pos_y),
    m_window(window),
    m_container(sf::RectangleShape(sf::Vector2(
       blockSize * m_blockCount_x + borderWidth * 2.f,
       blockSize * m_blockCount_y + borderWidth * 2.f 
    ))),
    m_tetrominoFactory(TetrominoFactory()),
    m_active(ActiveTetromino{m_tetrominoFactory.generateTetromino(), {INIT_POS_X, INIT_POS_Y}})
{
    m_container.setFillColor(sf::Color::Transparent);
    m_container.setOutlineThickness(borderWidth * -1.f);
    m_container.setOutlineColor(sf::Color(255, 255, 255));
    m_container.setPosition(pos_x, pos_y);

    for (int y = 0; y < m_blockCount_y; y++)
        for (int x = 0; x < m_blockCount_x; x++)
        {
            m_arr[y][x].setTetromino(-1, EMPTY);
            m_arr[y][x].setPosition(m_pos_x + m_borderWidth + x * m_blockSize, m_pos_y + m_borderWidth + y * m_blockSize);
        }
    placeActive({0, 0}, Direction::None);
}

void GameEntity::TetrominoContainer::placeActive(Vector offset, Direction dir)
{
    m_active.offset.x += offset.x;
    m_active.offset.y += offset.y;
    
    m_active.tetromino->rotate(dir);

    // paste tetromino positions to container m_arr 
    for (int i = 0; i < Tetromino::blockCount; i++)
    {
        const Vector v = m_active.tetromino->blockPosition[i];
        m_arr[v.y + m_active.offset.y][v.x + m_active.offset.x]
            .setTetromino(m_active.tetromino->id, m_active.tetromino->type);
    }
}

void GameEntity::TetrominoContainer::clearActive()
{
    for (int i = 0; i < Tetromino::blockCount; i++)
    {
        const Vector v = m_active.tetromino->blockPosition[i];
        m_arr[v.y + m_active.offset.y][v.x + m_active.offset.x].setEmpty();
    }    
}

void GameEntity::TetrominoContainer::rotateTetromino()
{
    const Vector *blocks = m_active.tetromino->peek();
    for (int i = 0; i < Tetromino::blockCount; i++)
    {
        std::cout << "Block #" << i << ": {" << blocks[i].x << ", " << blocks[i].y << "}" << std::endl;
    }
    
    int offset_x = 0;
    int offset_y = 0;

    // Offset x
    if (m_active.offset.x + ActiveTetromino::Offset_size > m_blockCount_x)
    {
        int limit = m_active.offset.x + ActiveTetromino::Offset_size - m_blockCount_x + 1;
        for (int tmp_offset = 0; tmp_offset < limit; tmp_offset++)
        {
            bool isRotatable = true;
            int offset = m_active.offset.x - tmp_offset;
            for (int i = 0; i < Tetromino::blockCount; i++)
            {
                int tmp_x = blocks[i].x + offset;
                if (tmp_x > m_blockCount_x - 1)
                {
                    isRotatable = false;
                    break;
                }
            }
            if (isRotatable)
            {
                offset_x = 0 - tmp_offset;
                break;
            } 
        }
    } else if (m_active.offset.x < 0)
    {
        int limit = 0 - m_active.offset.x + 1;
        for (int tmp_offset = 0; tmp_offset < limit; tmp_offset++)
        {
            bool isRotatable = true;
            int offset = m_active.offset.x + tmp_offset;
            for (int i = 0; i < Tetromino::blockCount; i++)
            {
                int tmp_x = blocks[i].x + offset;
                if (tmp_x < 0)
                {
                    isRotatable = false;
                    break;
                }
            }
            if (isRotatable)
            {
                offset_x = tmp_offset;
                break;
            }
        }
    }
    // Offset y
    if (m_active.offset.y + ActiveTetromino::Offset_size > m_blockCount_y)
    {
        int limit = m_active.offset.y + ActiveTetromino::Offset_size - m_blockCount_y + 1;

        for (int tmp_offset = 0; tmp_offset < limit; tmp_offset++)
        {
            bool isRotatable = true;
            int offset = m_active.offset.y - tmp_offset;
            for (int i = 0; i < Tetromino::blockCount; i++)
            {
                int tmp_y = blocks[i].y + offset;
                if (tmp_y > m_blockCount_y - 1)
                {
                    isRotatable = false;
                    break;
                }
            }
            if (isRotatable)
            {
                offset_y = 0 - tmp_offset;
                break;
            }
        }
    }
    clearActive();
    placeActive({offset_x, offset_y}, Direction::Clockwise);
}

void GameEntity::TetrominoContainer::moveRight()
{
    for (int i = 0; i < Tetromino::blockCount; i++)
    {
        // new x
        int x = m_active.tetromino->blockPosition[i].x + m_active.offset.x + 1;
        if (x > m_blockCount_x - 1)
            return;
    }
    clearActive();
    placeActive({1, 0}, Direction::None);
}

void GameEntity::TetrominoContainer::moveLeft()
{
    for (int i = 0; i < Tetromino::blockCount; i++)
    {
        // new x
        int x = m_active.tetromino->blockPosition[i].x + m_active.offset.x - 1;
        if (x < 0)
            return;
    }
    clearActive();
    placeActive({-1, 0}, Direction::None);
}

void GameEntity::TetrominoContainer::moveDown()
{
    for (int i = 0; i < Tetromino::blockCount; i++)
    {
        // new y
        int y = m_active.tetromino->blockPosition[i].y + m_active.offset.y + 1;
        if (y > m_blockCount_y - 1)
            return;
    }
    clearActive();
    placeActive({0, 1}, Direction::None);
}

void GameEntity::TetrominoContainer::drop()
{
    int offset = 0;
    while (true)
    {
        int curr_offset = m_active.offset.y + offset + 1;
        for (int i = 0; i < Tetromino::blockCount; i++)
        {
            if (m_active.tetromino->blockPosition[i].y + curr_offset > m_blockCount_y - 1)
            {
                clearActive();
                placeActive({0, offset}, Direction::None);
                nextActive();
                return;
            }
        }
        ++offset;
    }
}



void GameEntity::TetrominoContainer::nextActive()
{
    delete(m_active.tetromino);
    m_active = ActiveTetromino{
        m_tetrominoFactory.generateTetromino(),
        {INIT_POS_X, INIT_POS_Y}
    };
    placeActive({0, 0}, Direction::None);
}

void GameEntity::TetrominoContainer::drawBlocks()
{
    for (int y = 0; y < m_blockCount_y; y++)
        for (int x = 0; x < m_blockCount_x; x++)
            m_window->draw(m_arr[y][x].content);
}
void GameEntity::TetrominoContainer::drawContent()
{
    drawBlocks();
}

void GameEntity::TetrominoContainer::render()
{
    m_window->draw(m_container);
    drawContent();
}
GameEntity::TetrominoContainer::~TetrominoContainer()
{
}

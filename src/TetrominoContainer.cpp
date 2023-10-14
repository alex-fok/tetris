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
    placeActive();
}

void GameEntity::TetrominoContainer::placeActive()
{
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

void GameEntity::TetrominoContainer::moveRight()
{
    for (int i = 0; i < Tetromino::blockCount; i++)
    {
        int x = m_active.tetromino->blockPosition[i].x + m_active.offset.x;
        if (x + 2 > m_blockCount_x)
            return;
    }
    clearActive();
    m_active.offset.x += 1;
    placeActive();
}

void GameEntity::TetrominoContainer::moveLeft()
{
    for (int i = 0; i < Tetromino::blockCount; i++)
    {
        int x = m_active.tetromino->blockPosition[i].x + m_active.offset.x;
        if (x - 1 < 0)
            return;
    }
    clearActive();
    m_active.offset.x -= 1;
    placeActive();
}

void GameEntity::TetrominoContainer::moveDown()
{
    for (int i = 0; i < Tetromino::blockCount; i++)
    {
        int y = m_active.tetromino->blockPosition[i].y + m_active.offset.y;
        if (y + 2 > m_blockCount_y)
            return;
    }
    clearActive();
    m_active.offset.y += 1;
    placeActive();
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
                m_active.offset.y += offset;
                placeActive();
                return;
            }
        }
        ++offset;
    }
}

void GameEntity::TetrominoContainer::rotateTeromino()
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
    m_active.offset.x += offset_x;
    m_active.offset.y += offset_y;
    m_active.tetromino->rotate();
    placeActive();
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

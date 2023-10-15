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
    placeActive({0, 0}, Rotation::None);
}

bool GameEntity::TetrominoContainer::isStaticBlock(Vector v)
{
    Block b = m_arr[v.y][v.x];
    return b.t_id != -1 && b.t_id != m_active.tetromino->id;
}

void GameEntity::TetrominoContainer::placeActive(Vector offset, Rotation dir)
{
    // Update active offset and rotation
    m_active.offset.x += offset.x;
    m_active.offset.y += offset.y;
    
    m_active.tetromino->rotate(dir);

    // Update Ghost
    int ghost_offset = -1;
    bool ghostFound = false;
    while (!ghostFound)
    {
        ghost_offset++;
        int offset_x = m_active.offset.x;
        int offset_y = m_active.offset.y + ghost_offset + 1;
        Tetromino *active = m_active.tetromino;
        
        for (int i = 0; i < Tetromino::blockCount; i++)
        {
            int y = active->position[i].y + offset_y;
            int x = active->position[i].x + offset_x;
            if (y > m_blockCount_y - 1 || isStaticBlock({x, y}))
            {
                ghostFound = true;
                break;
            }
        }
    }
    m_active.ghost_y = ghost_offset;

    // Set Tetromino and Ghost
    for (int i = 0; i < Tetromino::blockCount; i++)
    {
        const Vector v = m_active.tetromino->position[i];
        m_arr[v.y + m_active.offset.y][v.x + m_active.offset.x]
            .setTetromino(m_active.tetromino->id, m_active.tetromino->type);

        if (ghost_offset)
            m_arr[v.y + m_active.offset.y + m_active.ghost_y][v.x + m_active.offset.x]
                .setGhost(m_active.tetromino->type);
    }
}

void GameEntity::TetrominoContainer::clearActive()
{
    for (int i = 0; i < Tetromino::blockCount; i++)
    {
        const Vector v = m_active.tetromino->position[i];
        m_arr[v.y + m_active.offset.y][v.x + m_active.offset.x].reset();
        m_arr[v.y + m_active.offset.y + m_active.ghost_y][v.x + m_active.offset.x].reset();
    }    
}

void GameEntity::TetrominoContainer::rotate()
{
    const Vector *blocks = m_active.tetromino->peek();
    
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
    placeActive({offset_x, offset_y}, Rotation::Clockwise);
}

void GameEntity::TetrominoContainer::moveRight()
{
    for (int i = 0; i < Tetromino::blockCount; i++)
    {
        // new x
        int x = m_active.tetromino->position[i].x + m_active.offset.x + 1;
        int y = m_active.tetromino->position[i].y + m_active.offset.y;
        if (x > m_blockCount_x - 1 || isStaticBlock({x, y}))
            return;
    }
    clearActive();
    placeActive({1, 0}, Rotation::None);
}

void GameEntity::TetrominoContainer::moveLeft()
{
    for (int i = 0; i < Tetromino::blockCount; i++)
    {
        // new x
        int x = m_active.tetromino->position[i].x + m_active.offset.x - 1;
        int y = m_active.tetromino->position[i].y + m_active.offset.y;
        if (x < 0 || isStaticBlock({x, y}))
            return;
    }
    clearActive();
    placeActive({-1, 0}, Rotation::None);
}

void GameEntity::TetrominoContainer::moveDown()
{
    for (int i = 0; i < Tetromino::blockCount; i++)
    {
        int x = m_active.tetromino->position[i].x + m_active.offset.x;
        // new y
        int y = m_active.tetromino->position[i].y + m_active.offset.y + 1;
        
        if (y > m_blockCount_y - 1 || isStaticBlock({x, y}))
            return;
    }
    clearActive();
    placeActive({0, 1}, Rotation::None);
}

void GameEntity::TetrominoContainer::drop()
{   
    clearActive();
    placeActive({0, m_active.ghost_y}, Rotation::None);
    nextActive();
}

void GameEntity::TetrominoContainer::nextActive()
{
    delete(m_active.tetromino);
    m_active = ActiveTetromino{
        m_tetrominoFactory.generateTetromino(),
        {INIT_POS_X, INIT_POS_Y}
    };
    placeActive({0, 0}, Rotation::None);
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

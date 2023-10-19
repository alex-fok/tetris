#pragma once
#include "TetrominoContainer.hpp"

GameEntity::TetrominoContainer::TetrominoContainer(sf::RenderWindow *window, float blockSize, float borderWidth, float pos_x, float pos_y) :
    m_blockSize(blockSize), m_borderWidth(borderWidth),
    m_pos_x(pos_x), m_pos_y(pos_y),
    m_window(window),
    m_container(sf::RectangleShape(sf::Vector2(
       blockSize * BlockCount_x + borderWidth * 2.f - BlockCount_x + 1,
       blockSize * BlockCount_y + borderWidth * 2.f - BlockCount_y + 1 
    ))),
    m_tetrominoFactory(TetrominoFactory()),
    m_active(ActiveTetromino{m_tetrominoFactory.generateTetromino(), {InitPos_X, InitPos_Y}})
{
    m_container.setFillColor(sf::Color::Transparent);
    m_container.setOutlineThickness(borderWidth * -1.f);
    m_container.setOutlineColor(sf::Color(255, 255, 255));
    m_container.setPosition(pos_x, pos_y);

    for (int y = 0; y < BlockCount_y; y++)
        for (int x = 0; x < BlockCount_x; x++)
            m_arr[y][x].setPosition(m_pos_x + m_borderWidth + x * m_blockSize - x, m_pos_y + m_borderWidth + y * m_blockSize - y);
        
    update();
}

bool GameEntity::TetrominoContainer::isBlocked(Vector v)
{    
    if (
        v.x < 0 || v.y < 0 ||
        v.x > BlockCount_x - 1 || v.y > BlockCount_y - 1
    )
        return true;
    
    Block b = m_arr[v.y][v.x];
    return b.t_id > -1 && b.t_id != m_active.tetromino->id;
}

void GameEntity::TetrominoContainer::update()
{
    // Update Ghost
    int ghost_offset = -1;
    bool ghostFound = false;
    while (ghostFound == false)
    {
        ++ghost_offset;
        int offset_x = m_active.offset.x;
        int offset_y = m_active.offset.y + ghost_offset + 1;
        
        Tetromino *active = m_active.tetromino;
        
        for (int i = 0; i < Tetromino::BlockCount; i++)
        {
            int y = active->position[i].y + offset_y;
            int x = active->position[i].x + offset_x;
            
            if (isBlocked({x, y}))
            {
                ghostFound = true;
                break;
            }
        }
    }
    m_active.ghost_y = ghost_offset;

    // Set Tetromino and Ghost
    for (int i = 0; i < Tetromino::BlockCount; i++)
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
    for (int i = 0; i < Tetromino::BlockCount; i++)
    {
        const Vector v = m_active.tetromino->position[i];
        m_arr[v.y + m_active.offset.y][v.x + m_active.offset.x].reset();
        m_arr[v.y + m_active.offset.y + m_active.ghost_y][v.x + m_active.offset.x].reset();
    }    
}

void GameEntity::TetrominoContainer::rotate(Tetromino::Rotation r)
{
    const Vector *next = m_active.tetromino->peek(r);
    const Vector *testOffsets = m_active.tetromino->getWallKickOffsets(r); 

    for (int i = 0; i < Tetromino::TestCount; i++)
    {
        bool success = true;
        for (int j = 0; j < Tetromino::BlockCount; j++)
        {
            int x = next[j].x + m_active.offset.x + testOffsets[i].x;
            int y = next[j].y + m_active.offset.y + testOffsets[i].y;
            if (isBlocked({x, y}))
            {
                success = false;
                break;
            }
        }
        if (success)
        {
            clearActive();
            m_active.offset.x += testOffsets[i].x;
            m_active.offset.y += testOffsets[i].y;
            m_active.tetromino->rotate(r);
            update();
            break;
        }
    }
}

void GameEntity::TetrominoContainer::moveRight()
{
    for (int i = 0; i < Tetromino::BlockCount; i++)
    {
        // new x
        int x = m_active.tetromino->position[i].x + m_active.offset.x + 1;
        int y = m_active.tetromino->position[i].y + m_active.offset.y;
        if (isBlocked({x, y}))
            return;
    }
    clearActive();
    m_active.offset.x += 1;
    update();
}

void GameEntity::TetrominoContainer::moveLeft()
{
    for (int i = 0; i < Tetromino::BlockCount; i++)
    {
        // new x
        int x = m_active.tetromino->position[i].x + m_active.offset.x - 1;
        int y = m_active.tetromino->position[i].y + m_active.offset.y;
        if (isBlocked({x, y}))
            return;
    }
    clearActive();
    m_active.offset.x -= 1;
    update();
}

void GameEntity::TetrominoContainer::moveDown()
{
    for (int i = 0; i < Tetromino::BlockCount; i++)
    {
        int x = m_active.tetromino->position[i].x + m_active.offset.x;
        // new y
        int y = m_active.tetromino->position[i].y + m_active.offset.y + 1;
        
        if (isBlocked({x, y}))
            return;
    }
    clearActive();
    m_active.offset.y += 1;
    update();
}

void GameEntity::TetrominoContainer::drop()
{   
    clearActive();
    m_active.offset.y += m_active.ghost_y;
    nextActive();
}

void GameEntity::TetrominoContainer::nextActive()
{
    for (int i = 0; i < Tetromino::BlockCount; i++)
    {
        const Vector v = m_active.tetromino->position[i];
        m_arr[v.y + m_active.offset.y][v.x + m_active.offset.x]
            .setTetromino(m_active.tetromino->id, m_active.tetromino->type);
    }
    delete(m_active.tetromino);
    m_active = ActiveTetromino{m_tetrominoFactory.generateTetromino(), {InitPos_X, InitPos_Y}};
    update();
}

void GameEntity::TetrominoContainer::drawBlocks()
{
    // Space
    for (int y = 0; y < BlockCount_y; y++)
        for (int x = 0; x < BlockCount_x; x++)
            if (m_arr[y][x].t_id == -1)
                m_window->draw(m_arr[y][x].content);
    // Solid blocks
    for (int y = 0; y < BlockCount_y; y++)
        for (int x = 0; x < BlockCount_x; x++)
            if (m_arr[y][x].t_id > -1)
                m_window->draw(m_arr[y][x].content);
    // Ghost
    for (int i = 0; i < Tetromino::BlockCount; i++)
    {
        const Vector v = m_active.tetromino->position[i];
        m_window->draw(m_arr[v.y + m_active.offset.y + m_active.ghost_y][v.x + m_active.offset.x].content);
    }
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

#include <unordered_map>
#include <chrono>
#include <thread>
#include "TetrominoContainer.hpp"
#include <iostream>

GameEntity::TetrominoContainer::TetrominoContainer(sf::RenderWindow *window, float blockSize, float borderWidth, GameUI::Position offset, std::function<void(GameUI::Status)> statusSetter) :
    Drawable(window),
    m_blockSize(blockSize), m_borderWidth(borderWidth),
    m_frame(sf::RectangleShape(sf::Vector2(
       blockSize * BlockCount_x + borderWidth * 2.f - BlockCount_x + 1,
       blockSize * BlockCount_y + borderWidth * 2.f - BlockCount_y + 1 
    ))),
    m_tetrominoFactory(TetrominoFactory()),
    m_active(ActiveTetromino(m_tetrominoFactory.generateTetromino(), {InitPos_x, InitPos_y})),
    m_setStatus(statusSetter)
{
    m_frame.setFillColor(sf::Color::Transparent);
    m_frame.setOutlineThickness(borderWidth * -1.f);
    m_frame.setOutlineColor(sf::Color(255, 255, 255));
    m_frame.setPosition(offset.x, offset.y);
    for (int y = 0; y < BlockCount_y; ++y)
        for (int x = 0; x < BlockCount_x; ++x)
        {
            // Note: reverse_y + y = BlockCount_y - 1. Ex: (0, 19), (1, 18), ..., (19, 0)
            int reverse_y = BlockCount_y - 1 - y;
            m_arr[y][x].setPosition(offset.x + m_borderWidth + x * m_blockSize - x, offset.y + m_borderWidth + reverse_y * (m_blockSize - 1));
        }
    updateActive();
}

void GameEntity::TetrominoContainer::reset()
{
    m_tetrominoFactory.reset();
    m_active = ActiveTetromino(m_tetrominoFactory.generateTetromino(), {InitPos_x, InitPos_y});
    for (int y = 0; y < BlockCount_y + ActiveTetromino::Offset_size; ++y)
        for (int x = 0; x < BlockCount_x; ++x)
            m_arr[y][x].reset();

    updateActive();
}

bool GameEntity::TetrominoContainer::isBlocked(Vector v)
{    
    if ( v.x < 0 || v.y < 0 || v.x > BlockCount_x - 1 )
        return true;
    
    return m_arr[v.y][v.x].t_id > -1 && m_arr[v.y][v.x].t_id != m_active.tetromino->id;
}

void GameEntity::TetrominoContainer::updateActive()
{
    // Update Ghost
    int ghost_offset = 1;
    bool ghostFound = false;
    while (ghostFound == false)
    {
        --ghost_offset;
        int offset_x = m_active.offset.x;
        int offset_y = m_active.offset.y + ghost_offset - 1;
        
        Tetromino *active = m_active.tetromino;
        
        for (int i = 0; i < Tetromino::BlockCount; ++i)
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
    for (int i = 0; i < Tetromino::BlockCount; ++i)
    {
        const Vector v = m_active.tetromino->position[i];
        m_arr[v.y + m_active.offset.y][v.x + m_active.offset.x]
            .setTetromino(m_active.tetromino->id, m_active.tetromino->type);

        if (ghost_offset)
        {
            m_arr[v.y + m_active.offset.y + m_active.ghost_y][v.x + m_active.offset.x].setGhost(m_active.tetromino->type);
            m_active.updateStat(ActiveTetromino::ActiveStat::Active);
        } else
            m_active.updateStat(ActiveTetromino::ActiveStat::CountDown);
    }
}

void GameEntity::TetrominoContainer::clearActive()
{
    for (int i = 0; i < Tetromino::BlockCount; ++i)
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

    for (int i = 0; i < Tetromino::TestCount; ++i)
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
            updateActive();
            break;
        }
    }
}

void GameEntity::TetrominoContainer::move(Vector v)
{
    bool isLanded = false;
    for (int i = 0; i < Tetromino::BlockCount; ++i)
    {
        // new x
        int x = m_active.tetromino->position[i].x + m_active.offset.x + v.x;
        int y = m_active.tetromino->position[i].y + m_active.offset.y + v.y;
        if (isBlocked({x, y}))
            return;
        if (isBlocked({x, y - 1}))
            isLanded = true;
    }
    clearActive();
    m_active.offset.x += v.x;
    m_active.offset.y += v.y;
    if (isLanded)
    {
        m_active.updateStat(ActiveTetromino::ActiveStat::CountDown);
        m_active.elapsed.restart();
    }
    updateActive();
}

void GameEntity::TetrominoContainer::drop()
{   
    clearActive();
    m_active.offset.y += m_active.ghost_y;
    m_active.ghost_y = 0;
    settleActive();
}

void GameEntity::TetrominoContainer::clearLines()
{
    for (std::vector<int>::reverse_iterator it = linesToClear.rbegin(); it != linesToClear.rend(); ++it)
        for (int yi = *it; yi < BlockCount_y - 1; ++yi)
            for (int xi = 0; xi < BlockCount_x; ++xi)
                m_arr[yi][xi].copy(m_arr[yi + 1][xi]);
     
    linesToClear.clear();
}

void GameEntity::TetrominoContainer::placeNewActive()
{
    // Set GameOver to true if active piece is settled above the top line
    for (int i = 0; i < Tetromino::BlockCount; ++i)
        if (m_active.tetromino->position[i].y + m_active.offset.y > BlockCount_y - 1)
        {
            m_setStatus(GameUI::Status::GameOver);
            delete(m_active.tetromino);
            return;
        }
    delete(m_active.tetromino);
    if (!linesToClear.empty())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));    
        clearLines();
    }
    Tetromino *t = m_tetrominoFactory.generateTetromino();
    // Find new start position
    int startPos_y = BlockCount_y;
    bool isLifted = false;
    for (bool isLifted = false; !isLifted && startPos_y > InitPos_y; --startPos_y)
    {
        for (int i = 0; i < Tetromino::BlockCount; ++i)
            if (isBlocked({t->position[i].x + InitPos_x, t->position[i].y + startPos_y - 1}))
            {
                isLifted = true;
                break;
            }
        if (isLifted)
            break;
    }
    m_active = ActiveTetromino(t, {InitPos_x, startPos_y});
    updateActive();
}

void GameEntity::TetrominoContainer::settleActive()
{
    std::unordered_map<int, bool> map;
    for (int i = 0; i < Tetromino::BlockCount; ++i)
    {
        const Vector v = m_active.tetromino->position[i];
        int x = m_active.offset.x + v.x;
        int y = m_active.offset.y + v.y;
        m_arr[y][x].setTetromino(m_active.tetromino->id, m_active.tetromino->type);
        
        // Check if line should be cleared
        if (!map.count(y))
        {
            bool isFilled = true;
            for (int xi = 0; xi < BlockCount_x; ++xi)
                if (m_arr[y][xi].t_id < 0)
                {
                    isFilled = false;
                    break;
                }
            if (isFilled)
            {
                map[y] = true;
                TetrominoContainer::linesToClear.push_back(y);   
            }
        }
    }
    m_active.updateStat(ActiveTetromino::Settled);
}

void GameEntity::TetrominoContainer::nextStep()
{
    if (m_active.isSettled())
        placeNewActive(); 
    else if (m_active.shouldSettle())
        settleActive();
    else if (m_active.shouldDrop())
        move({0, -1});
}

void GameEntity::TetrominoContainer::handle(sf::Keyboard::Key input)
{
    switch(input)
    {
        case sf::Keyboard::Up:
            rotate(Tetromino::Rotation::Clockwise);
            break;
        case sf::Keyboard::Right:
            move({1, 0});
            break;
        case sf::Keyboard::Down:
            move({0, -1});
            break;
        case sf::Keyboard::Left:
            move({-1, 0});
            break;
        case sf::Keyboard::Space:
            drop();
            break;
    }
}

void GameEntity::TetrominoContainer::drawBlocks()
{
    // Space
    for (int y = 0; y < BlockCount_y; ++y)
        for (int x = 0; x < BlockCount_x; ++x)
            if (m_arr[y][x].t_id == -1)
                draw(m_arr[y][x].content);
    // Solid blocks
    for (int y = 0; y < BlockCount_y; ++y)
        for (int x = 0; x < BlockCount_x; ++x)
            if (m_arr[y][x].t_id > -1)
                draw(m_arr[y][x].content);
    // Ghost if active is not settled
    if (m_active.stat != ActiveTetromino::Settled)
        for (int i = 0; i < Tetromino::BlockCount; ++i)
        {
            const Vector v = m_active.tetromino->position[i];
            int y = v.y + m_active.offset.y + m_active.ghost_y;
            if (y < BlockCount_y)
                draw(m_arr[y][v.x + m_active.offset.x].content);
        }
}

void GameEntity::TetrominoContainer::render()
{
    draw(m_frame);
    drawBlocks();
}

GameEntity::TetrominoContainer::~TetrominoContainer()
{
}

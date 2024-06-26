#include <unordered_map>
#include <chrono>
#include <thread>
#include "TetrominoContainer.hpp"
#include <iostream>

GameEntity::TetrominoContainer::TetrominoContainer(
    sf::RenderWindow *window,
    TetrominoFactory *tetroFactory,
    ScoringSystem *scoringSystem,
    GameSetting::Setting *setting,
    GameAnimation::ClearLines *clearLinesAnimation,
    std::function<Tetromino *(Tetromino *)> setHold,
    std::function<void(GameUI::Status)> statusSetter
) :
    Drawable(window),
    m_frame(sf::RectangleShape(sf::Vector2(
        GameUI::Config::TetrominoContainer::Width,
        GameUI::Config::TetrominoContainer::Height
    ))),
    m_tetrominoFactory(tetroFactory),
    m_scoringSystem(scoringSystem),
    m_setting(setting),
    m_clearLinesAnimation(clearLinesAnimation),
    m_active(ActiveTetromino(m_tetrominoFactory->getNext(), {m_initPos.x, m_initPos.y})),
    m_setHold(setHold),
    m_setStatus(statusSetter)
{
    auto blockSize = GameUI::Config::Block::Size;
    auto borderWidth = GameUI::Config::TetrominoContainer::BorderWidth;
    auto limit = GameUI::Config::TetrominoContainer::PosLimit;
    m_frame.setFillColor(sf::Color::Transparent);
    m_frame.setOutlineThickness(borderWidth * -1.f);
    m_frame.setOutlineColor(sf::Color(255, 255, 255));
    m_frame.setPosition(limit.Left, limit.Top);

    for (int y = 0; y < m_blockCount.y; ++y)
        for (int x = 0; x < m_blockCount.x; ++x)
        {
            // Note: reverse_y + y = BlockCount.y - 1. Ex: (0, 19), (1, 18), ..., (19, 0)
            int reverse_y = m_blockCount.y - 1 - y;
            m_arr[y][x].setPosition(limit.Left + borderWidth + x * blockSize - x, limit.Top + borderWidth + reverse_y * (blockSize - 1));
            m_arr[y][x].setBlockThemeSetter(std::bind(GameSetting::Setting::forwarder_applyBlockTheme, m_setting, &m_arr[y][x], std::placeholders::_1));
            m_setting->addBlockThemeSubscription(&m_arr[y][x]);
        }
    updateActive(true);
}

void GameEntity::TetrominoContainer::reset()
{
    m_tetrominoFactory->reset();
    m_active = ActiveTetromino(m_tetrominoFactory->getNext(), {m_initPos.x, m_initPos.y});
    for (int y = 0; y < m_blockCount.y + GameUI::Config::TetrominoContainer::HiddenLines; ++y)
        for (int x = 0; x < m_blockCount.x; ++x)
            m_arr[y][x].reset();

    updateActive(true);
}

bool GameEntity::TetrominoContainer::isBlocked(Vector v)
{    
    if ( v.x < 0 || v.y < 0 || v.x > m_blockCount.x - 1 )
        return true;
    
    return m_arr[v.y][v.x].t_id > -1 && m_arr[v.y][v.x].t_id != m_active.tetromino->id;
}

void GameEntity::TetrominoContainer::updateActive(bool isResetTimer)
{
    // Update Ghost
    int ghost_offset = 1;
    bool ghostFound = false;
    while (!ghostFound)
    {
        --ghost_offset;
        int offset_x = m_active.offset.x;
        int offset_y = m_active.offset.y + ghost_offset - 1;
        
        for (int i = 0; i < Tetromino::BlockCount; ++i)
            if (isBlocked({m_active.tetromino->position[i].x + offset_x, m_active.tetromino->position[i].y + offset_y}))
            {
                ghostFound = true;
                break;
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
            m_arr[v.y + m_active.offset.y + m_active.ghost_y][v.x + m_active.offset.x].setGhost(m_active.tetromino->type);
    }
    if (ghost_offset)
        m_active.updateStat(ActiveTetromino::ActiveStat::Active, isResetTimer);
    else
        m_active.updateStat(ActiveTetromino::ActiveStat::CountDown, isResetTimer);
}

void GameEntity::TetrominoContainer::clearActive()
{
    for (int i = 0; i < Tetromino::BlockCount; ++i)
    {
        const Vector v = m_active.tetromino->position[i];
        m_arr[v.y + m_active.offset.y][v.x + m_active.offset.x].reset();
        m_arr[v.y + m_active.offset.y + m_active.ghost_y][v.x + m_active.offset.x].reset();
    }
    m_active.isRotated = false;
    m_active.wallkickOffset = 0;
}

void GameEntity::TetrominoContainer::rotate(Tetromino::RotateDirection r)
{
    const Vector *next = m_active.tetromino->peek(r);
    const Vector *testOffsets = m_active.tetromino->getWallKickOffsets(r); 

    for (unsigned int i = 0; i < Tetromino::TestCount; ++i)
    {
        bool success = true;
        for (int j = 0; success == true && j < Tetromino::BlockCount; j++)
        {
            int x = next[j].x + m_active.offset.x + testOffsets[i].x;
            int y = next[j].y + m_active.offset.y + testOffsets[i].y;
            if (isBlocked({x, y}))
                success = false;
        }
        if (success)
        {
            clearActive();
            m_active.offset.x += testOffsets[i].x;
            m_active.offset.y += testOffsets[i].y;
            m_active.tetromino->rotate(r);
            m_active.isRotated = true;
            m_active.wallkickOffset = i;
            updateActive(false);
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
    updateActive(v.y < 0 ? true : false);
}

void GameEntity::TetrominoContainer::softDrop()
{
    move({0, -1});
    m_scoringSystem->updateDropScore(SoftDrop, 1);
}

void GameEntity::TetrominoContainer::hardDrop()
{   
    clearActive();
    m_active.offset.y += m_active.ghost_y;
    m_scoringSystem->updateDropScore(HardDrop, m_active.ghost_y * -1);
    m_active.ghost_y = 0;
    settleActive();
}

void GameEntity::TetrominoContainer::clearLines()
{
    for (std::vector<int>::reverse_iterator it = m_linesToClear.rbegin(); it != m_linesToClear.rend(); ++it)
        for (int yi = *it; yi < m_blockCount.y; ++yi)
            for (int xi = 0; xi < m_blockCount.x; ++xi)
                m_arr[yi][xi].copy(m_arr[yi + 1][xi]);
     
    m_linesToClear.clear();
}

bool GameEntity::TetrominoContainer::isGameOver()
{
    for (int i = 0; i < Tetromino::BlockCount; ++i)
        if (m_active.tetromino->position[i].y + m_active.offset.y > m_blockCount.y - 1)
        {
            m_setStatus(GameUI::Status::GameOver);
            delete(m_active.tetromino);
            return true;
        }
    return false;
}

GameEntity::Vector GameEntity::TetrominoContainer::getStartPos(Tetromino *t)
{
    int startPos_y = m_blockCount.y;
    for (bool isLifted = false; !isLifted && startPos_y > m_initPos.y; --startPos_y)
        for (int i = 0; i < Tetromino::BlockCount; ++i)
            if (isBlocked({t->position[i].x + m_initPos.x, t->position[i].y + startPos_y - 1}))
                return {m_initPos.x, startPos_y};
    return {m_initPos.x, m_initPos.y};
}

void GameEntity::TetrominoContainer::scoreOrContinue()
{
    // T-spin
    if (m_active.tetromino && m_active.tetromino->type == T && m_active.isRotated)
    {
        auto corners = m_active.tetromino->getTCorners();
        int frontBlocked = 0;
        int rearBlocked = 0;

        for (auto corner : corners.front)
            if (isBlocked({m_active.offset.x + corner.x, m_active.offset.y + corner.y}))
                frontBlocked++;

        for (auto corner : corners.rear)
            if (isBlocked({m_active.offset.x + corner.x, m_active.offset.y + corner.y}))
                rearBlocked++;

        bool is3Corner = frontBlocked + rearBlocked > 2;
        bool isTSpin = (frontBlocked == 2 && rearBlocked > 0) || m_active.wallkickOffset == Tetromino::TestCount - 1;
        // bool isMini = frontBlocked == 1 && rearBlocked == 2 

        if (m_linesToClear.empty())
        {
            m_scoringSystem->clearCombo();
            if (is3Corner)
                m_scoringSystem->updateTSpinScore(isTSpin ? T_Spin : Mini);
        }
        else
        {
            if (is3Corner)
                if (isTSpin)
                    switch(m_linesToClear.size())
                    {
                        case 1:
                            m_scoringSystem->updateTSpinScore(T_Spin_Single);
                            break;
                        case 2:
                            m_scoringSystem->updateTSpinScore(T_Spin_Double);
                            break;
                        case 3:
                            m_scoringSystem->updateTSpinScore(T_Spin_Triple);
                            break;
                    }
                else
                    switch (m_linesToClear.size())
                    {
                        case 1:
                            m_scoringSystem->updateTSpinScore(Mini_Single);
                            break;
                        case 2:
                            m_scoringSystem->updateTSpinScore(Mini_Double);
                            break;
                    }
            else   
                switch(m_linesToClear.size())
                {
                    case 1:
                        m_scoringSystem->updateLineScore(Single);
                        break;
                    case 2:
                        m_scoringSystem->updateLineScore(Double);
                        break;
                    case 3:
                        m_scoringSystem->updateLineScore(Triple);
                        break;
                }
        }
    }
    else
    {
        if (m_linesToClear.empty())
            m_scoringSystem->clearCombo();
        else
        {
            switch(m_linesToClear.size())
            {
                case 1:
                    m_scoringSystem->updateLineScore(Single);
                    break;
                case 2:
                    m_scoringSystem->updateLineScore(Double);
                    break;
                case 3:
                    m_scoringSystem->updateLineScore(Triple);
                    break;
                case 4:
                    m_scoringSystem->updateLineScore(Tetris);
                    break;
            }
        }
    }
}

void GameEntity::TetrominoContainer::placeNewActive()
{
    if (m_active.tetromino)
        delete(m_active.tetromino);
    if (!m_linesToClear.empty())
        clearLines();
    Tetromino *t = m_tetrominoFactory->getNext();
    m_active = ActiveTetromino(t, {m_initPos.x, m_initPos.y});
    m_active.offset = getStartPos(t);
    updateActive(true);
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
        if (map.count(y)) continue;

        // Check if line should be cleared
        bool isFilled = true;
        for (int xi = 0; isFilled && xi < m_blockCount.x; ++xi)
            if (m_arr[y][xi].t_id < 0)
            {
                isFilled = false;
                break;
            }

        if (isFilled)
        {
            map[y] = true;
            m_linesToClear.push_back(y);
        }
    }
    if (!m_linesToClear.empty())
        m_clearLinesAnimation->play(&m_linesToClear);

    m_active.updateStat(ActiveTetromino::Settled, false);
    scoreOrContinue();
}

void GameEntity::TetrominoContainer::switchTetro()
{
    if (m_active.isSwitched) return;
    clearActive();
    Tetromino *heldTetro = m_setHold(m_active.tetromino);
    if (!heldTetro) heldTetro = m_tetrominoFactory->getNext();
    m_active = ActiveTetromino(heldTetro, getStartPos(heldTetro), true);
    updateActive(true);
}

void GameEntity::TetrominoContainer::nextStep()
{
    if (m_active.isSettled() && !isGameOver())
        placeNewActive();
    else if (m_active.shouldSettle())
        settleActive();
    else if (m_active.shouldDrop())
        softDrop();
}

void GameEntity::TetrominoContainer::handle(sf::Keyboard::Key input)
{
    switch(input)
    {
        case sf::Keyboard::LShift:
        case sf::Keyboard::C:
            switchTetro();
            break;
        case sf::Keyboard::Up:
        case sf::Keyboard::X:
            rotate(Tetromino::RotateDirection::Clockwise);
            break;
        case sf::Keyboard::Z:
            rotate(Tetromino::RotateDirection::CounterClockwise);
            break;
        case sf::Keyboard::Right:
            move({1, 0});
            break;
        case sf::Keyboard::Down:
            softDrop();
            break;
        case sf::Keyboard::Left:
            move({-1, 0});
            break;
        case sf::Keyboard::Space:
            hardDrop();
            break;
    }
}

void GameEntity::TetrominoContainer::drawBlocks()
{
    // Space
    for (int y = 0; y < m_blockCount.y; ++y)
        for (int x = 0; x < m_blockCount.x; ++x)
            if (m_arr[y][x].t_id == -1)
                draw(m_arr[y][x].content);
    // Solid blocks
    for (int y = 0; y < m_blockCount.y; ++y)
        for (int x = 0; x < m_blockCount.x; ++x)
            if (m_arr[y][x].t_id > -1)
                draw(m_arr[y][x].content);
    // Ghost if active is not settled
    if (m_active.stat != ActiveTetromino::Settled)
        for (int i = 0; i < Tetromino::BlockCount; ++i)
        {
            const Vector v = m_active.tetromino->position[i];
            int y = v.y + m_active.offset.y + m_active.ghost_y;
            if (y < m_blockCount.y)
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

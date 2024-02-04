#include "ScoringSystem.hpp"

const int linesClearedScoring[5] = { 0, 100, 300, 500, 800 };
const int linePoints[5] = { 0, 1, 3, 5, 8 };

GameEntity::ScoringSystem::ScoringSystem() :
    m_score(0),
    m_level(1),
    m_cleared(0),
    m_combo(-1),
    m_isB2BActive(false)
{
}

void GameEntity::ScoringSystem::scoreSingle()
{
    m_score += m_level * 100 + m_combo * comboMultiplier * m_level;
    m_cleared += 1;
    m_isB2BActive = false;
}

void GameEntity::ScoringSystem::scoreDouble()
{
    m_score += m_level * 300 + m_combo * comboMultiplier * m_level;
    m_cleared += 2;
    m_isB2BActive = false;
}

void GameEntity::ScoringSystem::scoreTriple()
{
    m_score += m_level * 500 + m_combo * comboMultiplier * m_level;
    m_cleared += 3;
    m_isB2BActive = false;
}

void GameEntity::ScoringSystem::scoreTetris()
{
    m_score += m_level * 800 + m_combo * comboMultiplier * m_level;
    m_cleared += 4;
    m_isB2BActive = true;
}

void GameEntity::ScoringSystem::scoreSoftDrop(int count)
{
    m_score += count;
}

void GameEntity::ScoringSystem::scoreHardDrop(int count)
{
    m_score += count * 2;
}

void GameEntity::ScoringSystem::updateLineScore(LineAction action)
{
    m_combo++;

    switch(action)
    {
        case Single:
            scoreSingle();
            break;
        case Double:
            scoreDouble();
            break;
        case Triple:
            scoreTriple();
            break;
        case Tetris:
            scoreTetris();
            break;
    }
    if (m_cleared > 10)
    {
        m_cleared = 0;
        m_level++;
    }
    for (auto fn: m_subscribed_fns)
        fn(m_score);
}

void GameEntity::ScoringSystem::updateDropScore(DropAction action, int count)
{
    switch(action)
    {
        case SoftDrop:
            scoreSoftDrop(count);
            break;
        case HardDrop:
            scoreHardDrop(count);
            break;
    }
    for (auto fn: m_subscribed_fns)
        fn(m_score);
}

void GameEntity::ScoringSystem::clearCombo()
{
    m_combo = -1;
}

void GameEntity::ScoringSystem::addSubscription(std::function<void(int)> fn)
{
    m_subscribed_fns.push_back(fn);
}

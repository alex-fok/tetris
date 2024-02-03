#include "ScoringSystem.hpp"

const int linesClearedScoring[5] = { 0, 100, 300, 500, 800 };
const int linePoints[5] = { 0, 1, 3, 5, 8 };

GameEntity::ScoringSystem::ScoringSystem() :
    m_score(0),
    m_level(1),
    m_cleared(0)
{
}

int GameEntity::ScoringSystem::scoreSingle()
{
    return m_level * 100;
}

int GameEntity::ScoringSystem::scoreDouble()
{
    return m_level * 300;
}

int GameEntity::ScoringSystem::scoreTriple()
{
    return m_level * 500;
}

int GameEntity::ScoringSystem::scoreTetris()
{
    return m_level * 800;
}

int GameEntity::ScoringSystem::scoreSoftDrop(int count)
{
    return count;
}

int GameEntity::ScoringSystem::scoreHardDrop(int count)
{
    return count * 2;
}

void GameEntity::ScoringSystem::updateLineScore(LineAction action)
{
    switch(action)
    {
        case Single:
            m_score += scoreSingle();
            m_cleared += 1;
            break;
        case Double:
            m_score += scoreDouble();
            m_cleared += 2;
            break;
        case Triple:
            m_score += scoreTriple();
            m_cleared += 3;
            break;
        case Tetris:
            m_score += scoreTetris();
            m_cleared += 4;
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
            m_score += scoreSoftDrop(count);
            break;
        case HardDrop:
            m_score += scoreHardDrop(count);
            break;
    }
    for (auto fn: m_subscribed_fns)
        fn(m_score);
}

void GameEntity::ScoringSystem::addSubscription(std::function<void(int)> fn)
{
    m_subscribed_fns.push_back(fn);
}

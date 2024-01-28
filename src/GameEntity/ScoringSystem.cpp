#include "ScoringSystem.hpp"

const int linesClearedScoring[5] = { 0, 100, 300, 500, 800 };
const int linePoints[5] = { 0, 1, 3, 5, 8 };

GameEntity::ScoringSystem::ScoringSystem() :
    m_score(0),
    m_level(1),
    m_cleared(0)
{
}

void GameEntity::ScoringSystem::updateScore(int linesCleared)
{
    m_score += m_level * linesClearedScoring[linesCleared];
    m_cleared += linePoints[linesCleared];
    if (m_cleared > 10)
    {
        m_cleared = 0;
        m_level++;
    }
    for (auto fn: m_subscribed_fns)
        fn(m_score);
}

void GameEntity::ScoringSystem::addSubscription(std::function<void(int)> fn)
{
    m_subscribed_fns.push_back(fn);
}

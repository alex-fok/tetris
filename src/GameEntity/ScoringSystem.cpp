#include "ScoringSystem.hpp"

GameEntity::ScoringSystem::ScoringSystem(GameAnimation::Animation *animation) :
    m_animation(animation),
    m_score(0),
    m_level(1),
    m_cleared(0),
    m_combo(-1),
    m_isB2BActive(false)
{
}

void GameEntity::ScoringSystem::scoreSoftDrop(int count)
{
    m_score += count;
}

void GameEntity::ScoringSystem::scoreHardDrop(int count)
{
    m_score += count * 2;
}

void GameEntity::ScoringSystem::scoreSingle()
{
    m_animation->select(GameAnimation::AnimationType::Scoring, "Single");
    m_score += m_level * 100 + (++m_combo) * comboMultiplier * m_level;
    m_cleared += 1;
    m_isB2BActive = false;
}

void GameEntity::ScoringSystem::scoreDouble()
{
    m_animation->select(GameAnimation::AnimationType::Scoring, "Double");
    m_score += m_level * 300 + (++m_combo) * comboMultiplier * m_level;
    m_cleared += 3;
    m_isB2BActive = false;
}

void GameEntity::ScoringSystem::scoreTriple()
{
    m_animation->select(GameAnimation::AnimationType::Scoring, "Triple");
    m_score += m_level * 500 + (++m_combo) * comboMultiplier * m_level;
    m_cleared += 5;
    m_isB2BActive = false;
}

void GameEntity::ScoringSystem::scoreTetris()
{
    m_animation->select(GameAnimation::AnimationType::Scoring, "Tetris");
    m_score += m_level * ((m_isB2BActive ? 1200 : 800) + (++m_combo) * comboMultiplier);
    m_cleared += 8;
    m_isB2BActive = true;
}

void GameEntity::ScoringSystem::scoreTSpinMini()
{
    m_animation->select(GameAnimation::AnimationType::Scoring, "T-Spin Mini");
    m_score += m_level * 100;
    m_isB2BActive = false;
}

void GameEntity::ScoringSystem::scoreTSpinMiniSingle()
{
    m_animation->select(GameAnimation::AnimationType::Scoring, "T-Spin Mini Single");
    m_score += m_level * (200 + (++m_combo) * comboMultiplier);
    m_isB2BActive = true;
}

void GameEntity::ScoringSystem::scoreTSpinMiniDouble()
{
    m_animation->select(GameAnimation::AnimationType::Scoring, "T-Spin Mini Doube");
    m_score += m_level * ((m_isB2BActive ? 600 : 400) + (++m_combo) * comboMultiplier);
    m_isB2BActive = true;
}

void GameEntity::ScoringSystem::scoreTSpin()
{
    m_animation->select(GameAnimation::AnimationType::Scoring, "T-Spin");
    m_score += m_level * 400;
    m_isB2BActive = false;
}

void GameEntity::ScoringSystem::scoreTSpinSingle()
{
    m_animation->select(GameAnimation::AnimationType::Scoring, "T-Spin Single");
    m_score += m_level * ((m_isB2BActive ? 1200 : 800) + (++m_combo) * comboMultiplier);
    m_isB2BActive = true;
}

void GameEntity::ScoringSystem::scoreTSpinDouble()
{
    m_animation->select(GameAnimation::AnimationType::Scoring, "T-Spin Double");
    m_score += m_level * ((m_isB2BActive ? 1800 : 1200) + (++m_combo) * comboMultiplier);
    m_isB2BActive = true;
}

void GameEntity::ScoringSystem::scoreTSpinTriple()
{
    m_animation->select(GameAnimation::AnimationType::Scoring, "T-Spin Triple");
    m_score += m_level * ((m_isB2BActive ? 2400 : 1600) + (++m_combo) * comboMultiplier);
    m_isB2BActive = true;
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

void GameEntity::ScoringSystem::updateLineScore(LineAction action)
{
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

void GameEntity::ScoringSystem::updateTSpinScore(TSpinAction action)
{
    switch(action)
    {
        case Mini:
            scoreTSpinMini();
            break;
        case Mini_Single:
            scoreTSpinMiniSingle();
            break;
        case Mini_Double:
            scoreTSpinMiniDouble();
            break;
        case T_Spin:
            scoreTSpin();
            break;
        case T_Spin_Single:
            scoreTSpinSingle();
            break;
        case T_Spin_Double:
            scoreTSpinDouble();
            break;
        case T_Spin_Triple:
            scoreTSpinTriple();
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

void GameEntity::ScoringSystem::clearCombo()
{
    m_combo = -1;
}


void GameEntity::ScoringSystem::addSubscription(std::function<void(int)> fn)
{
    m_subscribed_fns.push_back(fn);
}

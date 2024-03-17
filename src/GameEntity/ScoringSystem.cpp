#include "ScoringSystem.hpp"
#include <sstream>

GameEntity::ScoringSystem::ScoringSystem(GameAnimation::Scoring *animation) :
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

void GameEntity::ScoringSystem::playAnimation(const char *type, int score)
{
    std::stringstream subtextStream;
    subtextStream << "+ " << score << " pt";
    m_animation->play(type, subtextStream.str().c_str());
}

void GameEntity::ScoringSystem::scoreHardDrop(int count)
{
    m_score += count * 2;
}

void GameEntity::ScoringSystem::scoreSingle()
{
    int score = m_level * 100 + (++m_combo) * comboMultiplier * m_level;
    m_score += score;
    m_cleared += 1;
    m_isB2BActive = false;
    playAnimation("Single", score);
}

void GameEntity::ScoringSystem::scoreDouble()
{
    int score = m_level * 300 + (++m_combo) * comboMultiplier * m_level;
    m_score += score;
    m_cleared += 3;
    m_isB2BActive = false;
    playAnimation("Double", score);
}

void GameEntity::ScoringSystem::scoreTriple()
{
    int score = m_level * 500 + (++m_combo) * comboMultiplier * m_level;
    m_score += score;
    m_cleared += 5;
    m_isB2BActive = false;
    playAnimation("Triple", score);
}

void GameEntity::ScoringSystem::scoreTetris()
{
    int score = m_level * ((m_isB2BActive ? 1200 : 800) + (++m_combo) * comboMultiplier);
    m_score += score;
    m_cleared += 8;
    m_isB2BActive = true;
    playAnimation("Tetris", score);
}

void GameEntity::ScoringSystem::scoreTSpinMini()
{
    int score = m_level * 100;
    m_score += score;
    m_isB2BActive = false;
    playAnimation("T-Spin Mini", score);
}

void GameEntity::ScoringSystem::scoreTSpinMiniSingle()
{
    int score = m_level * (200 + (++m_combo) * comboMultiplier);
    m_score += score;
    m_isB2BActive = true;
    playAnimation("T-Spin Mini Single", score);
}

void GameEntity::ScoringSystem::scoreTSpinMiniDouble()
{
    int score = m_level * ((m_isB2BActive ? 600 : 400) + (++m_combo) * comboMultiplier);
    m_score += score;
    m_isB2BActive = true;
    playAnimation("T-Spin Mini Doube", score);
}

void GameEntity::ScoringSystem::scoreTSpin()
{
    int score = m_level * 400;
    m_score += score;
    m_isB2BActive = false;
    playAnimation("T-Spin", score);
}

void GameEntity::ScoringSystem::scoreTSpinSingle()
{
    int score = m_level * ((m_isB2BActive ? 1200 : 800) + (++m_combo) * comboMultiplier);
    m_score += score;
    m_isB2BActive = true;
    playAnimation("T-Spin Single", score);
}

void GameEntity::ScoringSystem::scoreTSpinDouble()
{
    int score = m_level * ((m_isB2BActive ? 1800 : 1200) + (++m_combo) * comboMultiplier);
    m_score += score;
    m_isB2BActive = true;
    playAnimation("T-Spin Double", score);
}

void GameEntity::ScoringSystem::scoreTSpinTriple()
{
    int score = m_level * ((m_isB2BActive ? 2400 : 1600) + (++m_combo) * comboMultiplier);
    m_score += score;
    m_isB2BActive = true;
    playAnimation("T-Spin Triple", score);
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

#include <iostream>
#include "Animation.hpp"

GameAnimation::Animation::Animation(
    sf::RenderWindow *window,
    float playTime,
    std::function<void()> startAnimation,
    std::function<void()> stopAnimation
) :
    Drawable(window),
    m_isPlaying(false),
    m_playTime(playTime),
    m_startAnimation(startAnimation),
    m_stopAnimation(stopAnimation)
{
}

void GameAnimation::Animation::play()
{
    // Start playing
}

void GameAnimation::Animation::drawFrame()
{
    // Draw current frame
}

void GameAnimation::Animation::render()
{
    if (!m_isPlaying) return;
    drawFrame();
}

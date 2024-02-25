#include <iostream>
#include "Animation.hpp"

GameAnimation::Animation::Animation(
    sf::RenderWindow *window,
    std::function<void()> startAnimation,
    std::function<void()> stopAnimation
) :
    Drawable(window),
    m_isPlaying(false),
    m_frame(0),
    m_startAnimation(startAnimation),
    m_stopAnimation(stopAnimation)
{
    m_text.setFont(Resources::FontCollection::getInstance()->RobotoRegular);
}

void GameAnimation::Animation::select(AnimationType type, const char *text)
{
    m_text.setString(text);
    auto localBounds = m_text.getLocalBounds();
    m_text.setOrigin(localBounds.width / 2, localBounds.height / 2);
    m_text.setPosition(init_x, init_y);
    m_isPlaying = true;
    m_startAnimation();
    m_startTime.restart();
}

void GameAnimation::Animation::play()
{
    float elapsedTime = m_startTime.getElapsedTime().asSeconds();
    m_text.setPosition(init_x, init_y - elapsedTime * 100);
    if (elapsedTime >= 0.5f)
    {
        m_isPlaying = false;
        m_stopAnimation();
    }
}

void GameAnimation::Animation::render()
{
    if (!m_isPlaying) return;
    play();
    draw(m_text);
}

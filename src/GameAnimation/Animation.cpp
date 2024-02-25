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
    m_text.setPosition(400, 200);
    m_isPlaying = true;
    m_startAnimation();
}

void GameAnimation::Animation::play()
{
    auto position = m_text.getPosition();
    m_text.setPosition(position.x, position.y - 1);

    if (m_frame == 300)
    {
        m_frame = 0;
        m_isPlaying = false;
        m_stopAnimation();
    } else
        m_frame++;
}

void GameAnimation::Animation::render()
{
    if (!m_isPlaying) return;
    play();
    draw(m_text);
}

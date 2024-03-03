#include "Scoring.hpp"

GameAnimation::Scoring::Scoring(sf::RenderWindow *window, std::function<void()> setStartPlaying, std::function<void()> setStopPlaying) :
    Animation(window, 0.5f, setStartPlaying, setStopPlaying)
{
    m_text.setFont(Resources::FontCollection::getInstance()->RobotoRegular);
}

void GameAnimation::Scoring::play(const char *text)
{    
    m_text.setString(text);
    auto localBounds = m_text.getLocalBounds();
    m_text.setOrigin(localBounds.width / 2, localBounds.height / 2);
    m_text.setPosition(init_x, init_y);
    m_isPlaying = true;
    m_startAnimation();
    m_startTime.restart();
}

void GameAnimation::Scoring::drawFrame()
{
    float elapsedTime = m_startTime.getElapsedTime().asSeconds();
    m_text.setPosition(init_x, init_y - elapsedTime * 100);
    draw(m_text);
    if (elapsedTime >= m_playTime)
    {
        m_isPlaying = false;
        m_stopAnimation();
    }
}

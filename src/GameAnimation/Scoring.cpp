#include "Scoring.hpp"

GameAnimation::Scoring::Scoring(sf::RenderWindow *window, std::function<void()> startPlaying, std::function<void()> stopPlaying) :
    Animation(window, GameUI::Config::Animation::Scoring::Duration, startPlaying, stopPlaying)
{
    m_text.setFont(Resources::FontCollection::getInstance()->RobotoRegular);
    m_subtext.setFont(Resources::FontCollection::getInstance()->RobotoRegular);
}

void GameAnimation::Scoring::play(const char *text, const char *subtext)
{    
    m_text.setString(text);
    auto textLocalBounds = m_text.getLocalBounds();
    m_text.setOrigin(textLocalBounds.width / 2, textLocalBounds.height / 2);
    m_text.setPosition(init_x, init_y);
    
    m_subtext.setString(subtext);
    m_subtext.setCharacterSize(18);
    auto subtextLocalBounds = m_subtext.getLocalBounds();
    m_subtext.setOrigin(subtextLocalBounds.width / 2, subtextLocalBounds.height / 2);
    m_subtext.setPosition(init_x, init_y + 50);

    m_isPlaying = true;
    m_startAnimation();
    m_startTime.restart();
}

void GameAnimation::Scoring::drawFrame()
{
    float elapsedTime = m_startTime.getElapsedTime().asSeconds();
    if (elapsedTime < m_playTime)
    {
        m_text.setPosition(init_x, init_y - elapsedTime * 100);
        m_subtext.setPosition(init_x, init_y - elapsedTime * 100 + 50);
        draw(m_text);
        draw(m_subtext);
    }
    else
    {
        m_isPlaying = false;
        m_stopAnimation();
    }
}

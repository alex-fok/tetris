#include "ClearLines.hpp"

GameAnimation::ClearLines::ClearLines(sf::RenderWindow *window, std::function<void()> startAnimation, std::function<void()> stopAnimation) :
    Animation(window, GameUI::Config::Animation::ClearLines::Duration, startAnimation, stopAnimation)
{
}

void GameAnimation::ClearLines::addLineRect(int lineNum)
{
    sf::RectangleShape *line = new sf::RectangleShape();
    line->setFillColor(sf::Color::White);
    line->setPosition(
        GameUI::Config::TetrominoContainer::PosLimit.Left + GameUI::Config::TetrominoContainer::BorderWidth,
        GameUI::Config::TetrominoContainer::PosLimit.Bottom - GameUI::Config::TetrominoContainer::BorderWidth - (GameUI::Config::Block::Size - 1) * (lineNum + 1)
    );
    line->setSize({GameUI::Config::TetrominoContainer::LineWidth, GameUI::Config::Block::Size});
    m_linesToClear.push_back(line);
}

void GameAnimation::ClearLines::play(std::vector<int> *lines)
{
    for (std::vector<int>::iterator it = lines->begin(); it != lines->end(); ++it)
        addLineRect(*it);
    m_isPlaying = true;
    m_startAnimation();
    m_startTime.restart();
}

void GameAnimation::ClearLines::drawFrame()
{
    float elapsedTime = m_startTime.getElapsedTime().asSeconds();
    if (elapsedTime < m_playTime)
    {
        sf::Color color = ((int) ((elapsedTime / m_playTime) / 0.2f)) % 2 == 1 ? sf::Color::Transparent : sf::Color::Black;
        for (std::vector<sf::RectangleShape *>::iterator it = m_linesToClear.begin(); it != m_linesToClear.end(); ++it)
        {
            (*it)->setFillColor(color);
            draw(**it);
        }
    }
    else
    {
        for (std::vector<sf::RectangleShape *>::iterator it = m_linesToClear.begin(); it != m_linesToClear.end(); ++it)
            delete(*it);

        m_linesToClear.clear();
        m_isPlaying = false;
        m_stopAnimation();
    }
}

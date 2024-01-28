#include "Score.hpp"
#include <iostream>

GameEntity::Score::Score(sf::RenderWindow *window) :
    Drawable(window),
    m_score(0),
    m_text(sf::Text()),
    m_score_text(sf::Text())
{
    namespace Score = GameUI::Config::Score;
    namespace ScoreText = Score::ScoreText;

    m_text.setFont(Resources::FontCollection::getInstance()->RobotoRegular);
    m_text.setString("Score");
    auto text_localBounds = m_text.getLocalBounds();
    m_text.setOrigin(text_localBounds.width / 2, text_localBounds.height / 2);
    m_text.setPosition((Score::PosLimit.Right - Score::PosLimit.Left) / 2, text_localBounds.height / 2 + Score::PosLimit.Top);
    m_text.setColor(sf::Color::White);

    m_score_text.setFont(Resources::FontCollection::getInstance()->RobotoRegular);
    m_score_text.setString(std::to_string(m_score));
    auto scoreText_localBounds = m_score_text.getLocalBounds();
    m_score_text.setOrigin(scoreText_localBounds.width / 2, scoreText_localBounds.height / 2);
    m_score_text.setPosition((Score::PosLimit.Right - Score::PosLimit.Left) / 2, Score::PosLimit.Top + text_localBounds.height + ScoreText::Margin_Top + scoreText_localBounds.height/ 2);
    m_score_text.setColor(sf::Color::White);    
}

void GameEntity::Score::updateScore(int linesCleared)
{
    m_score += linesCleared;
    m_score_text.setString(std::to_string(m_score));
}

void GameEntity::Score::render()
{
    draw(m_text);
    draw(m_score_text);
}

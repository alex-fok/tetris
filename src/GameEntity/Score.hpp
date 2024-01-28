#pragma once
#include "SFML/Graphics.hpp"
#include "../Resources/FontCollection.hpp"
#include "../GameUI/Config.hpp"
#include "../Utils/Drawable.hpp"
#include "ScoringSystem.hpp"

namespace GameEntity
{
    class Score : public Utils::Drawable
    {
    private:
        sf::RenderWindow *m_window;
        ScoringSystem *m_scoringSystem;
        sf::Text m_text;
        sf::Text m_score_text;
    public:
        Score(sf::RenderWindow *window, ScoringSystem *scoringSystem);
        void updateScore(int score);
        static void forwarder_updateScore(GameEntity::Score *, int score);
        void render();
    };
}

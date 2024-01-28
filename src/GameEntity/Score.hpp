#pragma once
#include "SFML/Graphics.hpp"
#include "../Resources/FontCollection.hpp"
#include "../Utils/Drawable.hpp"
#include "../GameUI/Config.hpp"

namespace GameEntity
{
    class Score : public Utils::Drawable
    {
    private:
        sf::RenderWindow *m_window;
        int m_score;
        sf::Text m_text;
        sf::Text m_score_text;
    public:
        Score(sf::RenderWindow *window);
        void updateScore(int linesCleared);
        void render();
    };
}

#pragma once
#include "SFML/Graphics.hpp"
#include "../Resources/FontCollection.hpp"
#include "Animation.hpp"

namespace GameAnimation {
    class Scoring : public Animation
    {
    private:
        sf::Text m_text;
        static constexpr float init_x = 400.f;
        static constexpr float init_y = 250.f;
    public:
        Scoring(sf::RenderWindow *window, std::function<void()> setStartPlaying, std::function<void()> setStopPlaying);
        void play(const char *text);
        void drawFrame();
    };
}

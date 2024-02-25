#pragma once
#include <functional>
#include "../Resources/FontCollection.hpp"
#include "../Utils/Drawable.hpp"
#include "../GameUI/Status.hpp"
#include "SFML/Graphics.hpp"
#include "AnimationType.hpp"

namespace GameAnimation {
    class Animation : public Utils::Drawable
    {
    private:
        sf::RenderWindow *m_window;
        sf::Clock m_startTime;
        unsigned m_frame;
        bool m_isPlaying;
        sf::Text m_text;
        static constexpr float init_x = 400.f;
        static constexpr float init_y = 200.f;
        std::function<void()> m_startAnimation;
        std::function<void()> m_stopAnimation;
    public:
        Animation(sf::RenderWindow *window, std::function<void()> setStartPlaying, std::function<void()> setStopPlaying);
        void select(AnimationType type, const char *text);
        void play();
        void render();
    };
}

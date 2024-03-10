#pragma once
#include <functional>
#include "SFML/Graphics.hpp"
#include "../Utils/Drawable.hpp"
#include "../GameUI/Config.hpp"
#include "../GameUI/Status.hpp"

namespace GameAnimation {
    class Animation : public Utils::Drawable
    {
    protected:
        sf::RenderWindow *m_window;
        sf::Clock m_startTime;
        bool m_isPlaying;
        float m_playTime;
        std::function<void()> m_startAnimation;
        std::function<void()> m_stopAnimation;
    public:
        Animation(sf::RenderWindow *window, float playTime, std::function<void()> setStartPlaying, std::function<void()> setStopPlaying);
        virtual void play();
        virtual void drawFrame();
        void render();
    };
}

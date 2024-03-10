#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "Animation.hpp"

namespace GameAnimation {
    class ClearLines : public Animation
    {
    private:
        std::vector<sf::RectangleShape *> m_linesToClear;
    public:
        ClearLines(sf::RenderWindow *window, std::function<void()> startAnimation, std::function<void()> stopAnimation);
        void addLineRect(int lineNum);
        void removeLineRects();
        void play(std::vector<int> *lines);
        void drawFrame();
    };
}

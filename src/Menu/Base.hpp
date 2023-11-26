#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "../Resources/FontCollection.hpp"
#include "../Utils/Drawable.hpp"
#include "../Utils/Button.hpp"

namespace Menu
{
    struct Offset
    {
        float top;
        float right;
        float down;
        float left;
    };
    class Base : public Utils::Drawable
    {
    private:
        Offset m_offset;
        sf::Vector2f m_size;
    protected:
        Resources::FontCollection *fontCollection;
        sf::RenderWindow *m_window;
        sf::RectangleShape m_container;
        sf::Text m_title;

    public:
        Base(sf::RenderWindow *w, sf::Vector2f v, const char *title);
        void setButtonPositions(std::vector<Utils::Button *> btns);
        void renderBase();
        virtual void render();
    };
}

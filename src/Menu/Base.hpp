#pragma once
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
        int m_selected;
        sf::CircleShape m_cursor;
    protected:
        Resources::FontCollection *fontCollection;
        sf::RenderWindow *m_window;
        sf::RectangleShape m_container;
        sf::Text m_title;
        void m_setup(float width, float height, const char *title);
        void m_setButtonPositions();
        void m_renderBase();
    public:
        Base(sf::RenderWindow *w);
        void setSelectedIdx(unsigned int idx);
        void handle(sf::Keyboard::Key input);
        virtual void render();
        static void forwarder_setSelected(Menu::Base *self, unsigned int idx);
    };
}

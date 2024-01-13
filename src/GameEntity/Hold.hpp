#pragma once
#include "SFML/Graphics.hpp"
#include "../Utils/Drawable.hpp"
#include "SingleTetroBox.hpp"
#include "Tetromino.hpp"

namespace GameEntity
{
    class Hold : public Utils::Drawable
    {
    private:
        Tetromino *m_tetromino;
        SingleTetroBox m_hold;
    public:
        Hold(sf::RenderWindow *window);
        Tetromino *switchTetro(Tetromino *active);
        void render();
        static Tetromino *forwarder_switchTetro(Hold *hold, Tetromino *tetromino);
    };
}

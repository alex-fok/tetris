#pragma once
#include "SFML/Graphics.hpp"
#include "../Resources/FontCollection.hpp"
#include "../Utils/Drawable.hpp"
#include "../GameSetting/Setting.hpp"
#include "SingleTetroBox.hpp"
#include "Tetromino.hpp"

namespace GameEntity
{
    class Hold : public Utils::Drawable
    {
    private:
        Tetromino *m_tetromino;
        SingleTetroBox m_hold;
        sf::Text m_text;
    public:
        Hold(sf::RenderWindow *, GameSetting::Setting *);
        Tetromino *switchTetro(Tetromino *active);
        void render();
        static Tetromino *forwarder_switchTetro(Hold *hold, Tetromino *tetromino);
    };
}

#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "../GameUI/Config.hpp"
#include "../Utils/Drawable.hpp"
#include "Tetromino.hpp"
#include "TetrominoFactory.hpp"
#include "Vector.hpp"
#include "Block.hpp"
#include "SingleTetroBox.hpp"

namespace GameEntity
{
    class PreviewList : public Utils::Drawable
    {
    private:
        static const sf::Vector2f relativePos[Tetromino::TypeCount][Tetromino::BlockCount];
        sf::RenderWindow *m_window;
        TetrominoFactory *m_tetroFactory;
        GameEntity::SingleTetroBox m_next;
        GameEntity::SingleTetroBox m_inLine[GameUI::Config::PreviewList::Count - 1];
   public:
        Tetromino **m_tetros;
        PreviewList(sf::RenderWindow *window, TetrominoFactory *tetroFactory);
        void update();
        static void forwarder_update(PreviewList *self);
        void render();
        ~PreviewList();
    };
}

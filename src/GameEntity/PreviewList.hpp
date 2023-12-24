#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "../GameUI/Config.hpp"
#include "../Utils/Drawable.hpp"
#include "TetrominoFactory.hpp"
#include "Block.hpp"

namespace GameEntity
{
    class PreviewList : public Utils::Drawable
    {
    private:
        sf::RenderWindow *m_window;
        TetrominoFactory *m_tetroFactory;
        sf::RectangleShape m_next;
        sf::RectangleShape m_inLine[GameUI::Config::PreviewList::Count - 1];
        GameEntity::Block m_next_blocks[4][4];
        GameEntity::Block m_inLine_blocks[GameUI::Config::PreviewList::Count - 1][4][4];
    public:
        Tetromino **m_tetros;
        PreviewList(sf::RenderWindow *window, TetrominoFactory *tetroFactory);
        void update();
        static void forwarder_update(PreviewList *self);
        void render();
        ~PreviewList();
    };
}

#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "../Resources/FontCollection.hpp"
#include "../Utils/Drawable.hpp"
#include "../GameUI/Config.hpp"
#include "../GameSetting/Setting.hpp"
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
        sf::Text m_text;
   public:
        Tetromino **m_tetros;
        PreviewList(sf::RenderWindow *, TetrominoFactory *, GameSetting::Setting *);
        void update();
        static void forwarder_update(PreviewList *);
        void render();
        ~PreviewList();
    };
}

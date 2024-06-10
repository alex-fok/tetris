#pragma once
#include "SFML/Graphics.hpp"
#include "../Utils/Drawable.hpp"
#include "../GameSetting/Setting.hpp"
#include "Tetromino.hpp"
#include "Block.hpp"

namespace GameEntity
{
    class SingleTetroBox : public Utils::Drawable
    {
    private:
        static const sf::Vector2f relativePos[Tetromino::TypeCount][Tetromino::BlockCount];
        GameSetting::Setting *m_setting;
        float m_blockSize;
        sf::Vector2f m_pos;
        sf::RectangleShape m_box;
        GameEntity::Block m_blocks[Tetromino::BlockCount];
    public:
        SingleTetroBox();
        SingleTetroBox(sf::RenderWindow *, GameSetting::Setting *);
        void init(float size, sf::Vector2f pos, float outlineThickness, float tetroBlockSize);
        void updateTetromino(GameEntity::BlockType type);
        void reset();
        void render();
    };
}

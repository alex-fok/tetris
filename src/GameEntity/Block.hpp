#pragma once
#include <SFML/Graphics.hpp>
#include "BlockType.hpp"
#include "Vector.hpp"

namespace GameEntity {
    static const sf::Color BlockColor[] =
    {
        sf::Color(0, 255, 255), // I, Cyan
        sf::Color(255, 255, 0), // O, Yellow
        sf::Color(255, 0, 255), // T, Magneta
        sf::Color(0, 0, 255), // J, Blue
        sf::Color(255, 165, 0), // L, Orange
        sf::Color(0, 255, 0), // S, Green
        sf::Color(255, 0, 0) //Z, Red
    };

    static const sf::Color OutlineColor_Default = sf::Color(64, 64, 64);

    class Block
    {
    public:
        int t_id;
        BlockType type;
        sf::RectangleShape content;
        Block(int id, BlockType type, float size);
        Block();
        void copy(Block &other);
        void setTetromino(int id, GameEntity::BlockType);
        void setOutline(GameEntity::BlockType);
        void reset();
        void setSize(sf::Vector2f v);
        void setPosition(float x, float y);
    };
}

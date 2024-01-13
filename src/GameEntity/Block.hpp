#pragma once
#include <SFML/Graphics.hpp>
#include "Vector.hpp"

namespace GameEntity {
    enum BlockType
    {
        EMPTY = -1, I, O, T, J, L, S, Z
    };

    static const sf::Color BlockColor[] =
    {
        sf::Color::Color(0, 255, 255), // I, Cyan
        sf::Color::Color(255, 255, 0), // O, Yellow
        sf::Color::Color(255, 0, 255), // T, Magneta
        sf::Color::Color(0, 0, 255), // J, Blue
        sf::Color::Color(255, 165, 0), // L, Orange
        sf::Color::Color(0, 255, 0), // S, Green
        sf::Color::Color(255, 0, 0) //Z, Red
    };

    static const sf::Color OutlineColor_Default = sf::Color::Color(64, 64, 64);

    static const sf::Color OutlineColor[] =
    {
        sf::Color::Color(0, 255, 255), // I, Cyan
        sf::Color::Color(255, 255, 0), // O, Yellow
        sf::Color::Color(255, 0, 255), // T, Magneta
        sf::Color::Color(0, 0, 255), // J, Blue
        sf::Color::Color(255, 165, 0), // L, Orange
        sf::Color::Color(0, 255, 0), // S, Green
        sf::Color::Color(255, 0, 0) //Z, Red
    };

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

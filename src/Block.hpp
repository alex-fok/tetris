#pragma once
#include <SFML/Graphics.hpp>
#include "Vector.hpp"

namespace GameEntity {
    const static float BlockSize = 29.f;
    
    enum BlockType
    {
        EMPTY = 0, I, O, T, J, L, S, Z
    };

    

    static const sf::Color BlockColor[] =
    {
        sf::Color::Transparent,
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
        sf::Color::Transparent,
        sf::Color::Color(0, 255, 255, 223), // I, Cyan
        sf::Color::Color(255, 255, 0, 223), // O, Yellow
        sf::Color::Color(255, 0, 255, 223), // T, Magneta
        sf::Color::Color(0, 0, 255, 223), // J, Blue
        sf::Color::Color(255, 165, 0, 223), // L, Orange
        sf::Color::Color(0, 255, 0, 223), // S, Green
        sf::Color::Color(255, 0, 0, 223) //Z, Red
    };

    class Block
    {
    public:
        int t_id;
        BlockType type;
        sf::RectangleShape content;
        Block(int id, BlockType type);
        Block();
        void setTetromino(int id, GameEntity::BlockType);
        void setGhost(GameEntity::BlockType);
        void reset();
        void setPosition(float x, float y);
    };
}

#include <SFML/Graphics.hpp>
#include "Block.hpp"
#include <iostream>

GameEntity::Block::Block(int id, GameEntity::BlockType type) :
    t_id(id),
    type(type),
    content(sf::RectangleShape(sf::Vector2(GameEntity::BlockSize, GameEntity::BlockSize)))
{
    content.setFillColor(GameEntity::BlockColor[type]);
    content.setOutlineThickness(-1.f);
    content.setOutlineColor(sf::Color::Color(64, 64, 64));
}

GameEntity::Block::Block() :
    GameEntity::Block::Block(-1, GameEntity::BlockType::EMPTY)
{
};

void GameEntity::Block::setTetromino(int id, GameEntity::BlockType type)
{
    t_id = id;
    content.setFillColor(GameEntity::BlockColor[type]);
}

void GameEntity::Block::setEmpty()
{
    setTetromino(-1, GameEntity::BlockType::EMPTY);
}

void GameEntity::Block::setPosition(float x, float y)
{
    content.setPosition(x, y);
}

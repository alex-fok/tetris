#include <SFML/Graphics.hpp>
#include "Block.hpp"

GameEntity::Block::Block(int id, BlockType type) :
    t_id(id),
    type(type),
    content(sf::RectangleShape(sf::Vector2(BlockSize, BlockSize)))
{
    content.setFillColor(type == EMPTY ? sf::Color::Transparent : BlockColor[type]);
    content.setOutlineThickness(-1.f);
    content.setOutlineColor(OutlineColor_Default);
}

GameEntity::Block::Block() :
    Block::Block(-1, EMPTY)
{
};

void GameEntity::Block::setTetromino(int id, BlockType type)
{
    t_id = id;
    content.setFillColor(BlockColor[type]);
    content.setOutlineColor(OutlineColor_Default);
}

void GameEntity::Block::setGhost(BlockType type)
{
    t_id = -2;
    content.setOutlineColor(BlockColor[type]);
}

void GameEntity::Block::reset()
{
    setTetromino(-1, EMPTY);
}

void GameEntity::Block::setPosition(float x, float y)
{
    content.setPosition(x, y);
}

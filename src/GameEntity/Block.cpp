#include "Block.hpp"
#include "../GameUI/Config.hpp"

GameEntity::Block::Block(int id, BlockType type, float size) :
    t_id(id),
    type(type),
    content(sf::RectangleShape(sf::Vector2(size, size)))
{
    content.setFillColor(type == EMPTY ? sf::Color::Transparent : BlockColor[type]);
    content.setOutlineThickness(-1.f);
    content.setOutlineColor(OutlineColor_Default);
}

GameEntity::Block::Block() :
    Block::Block(-1, EMPTY, GameUI::Config::Block::Size)
{
};

void GameEntity::Block::copy(GameEntity::Block &other)
{
    t_id = other.t_id;
    type = other.type;
    content.setFillColor(other.content.getFillColor());
    content.setOutlineThickness(other.content.getOutlineThickness());
    content.setOutlineColor(other.content.getOutlineColor());
}

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

void GameEntity::Block::setSize(sf::Vector2f v)
{
    content.setSize(v);
}

void GameEntity::Block::setPosition(float x, float y)
{
    content.setPosition(x, y);
}

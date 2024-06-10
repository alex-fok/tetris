#include "Block.hpp"
#include "../GameUI/Config.hpp"

GameEntity::Block::Block(int id, BlockType bType, float size) :
    t_id(id),
    type(bType),
    content(sf::RectangleShape(sf::Vector2(size, size)))
{
    content.setOutlineThickness(-1.f);
    content.setOutlineColor(OutlineColor_Default);
    content.setFillColor(type == EMPTY ? sf::Color::Transparent : BlockColor[type]);
}

GameEntity::Block::Block() :
    // t_id(-1),
    // type(EMPTY),
    // content(sf::RectangleShape(sf::Vector2(GameUI::Config::Block::Size, GameUI::Config::Block::Size)))
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

void GameEntity::Block::setBlockThemeSetter(std::function<void(BlockType)> blockThemeSetter) {
    m_applyTheme = blockThemeSetter;
    m_applyTheme(type);
}

void GameEntity::Block::setTetromino(int id, BlockType bType)
{
    t_id = id;
    if (!m_applyTheme)
    {
        content.setOutlineColor(OutlineColor_Default);
        content.setFillColor(bType == EMPTY ? sf::Color::Transparent : BlockColor[bType]);
    } else
        m_applyTheme(bType);
    
}

void GameEntity::Block::setOutline(BlockType bType)
{
    content.setOutlineColor(BlockColor[bType]);
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

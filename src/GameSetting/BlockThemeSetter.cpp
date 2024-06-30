#include "BlockThemeSetter.hpp"
#include <iostream>
GameSetting::BlockThemeSetter::BlockThemeSetter() :
    m_blockTheme(none)
{
}

void GameSetting::BlockThemeSetter::setBlockTheme(BlockTheme theme)
{
    m_blockTheme = theme;
    for (std::vector<GameEntity::Block *>::iterator it = m_blocks.begin(); it != m_blocks.end(); ++it)
        applyBlockTheme(*it, (*it)->type);
}

void GameSetting::BlockThemeSetter::addBlockThemeSubscription(GameEntity::Block *block)
{
    m_blocks.push_back(block);
}

void GameSetting::BlockThemeSetter::applyNone(GameEntity::Block *block, GameEntity::BlockType type)
{
    block->content.setFillColor(type == GameEntity::BlockType::EMPTY ? sf::Color::Transparent : BlockColor[type]);
    block->setOutline(GameEntity::BlockType::EMPTY);
    block->content.setTexture(NULL);
}

void GameSetting::BlockThemeSetter::applyWoodTexture(GameEntity::Block *block, GameEntity::BlockType type)
{
    block->content.setFillColor(type == GameEntity::BlockType::EMPTY ? sf::Color::Transparent : BlockColor[type]);
    block->setOutline(GameEntity::BlockType::EMPTY);
    block->content.setTexture(&Resources::BlockTextureCollection::getInstance()->Wooden);
}

void GameSetting::BlockThemeSetter::applyGrassTexture(GameEntity::Block *block, GameEntity::BlockType type)
{
    block->content.setFillColor(type == GameEntity::BlockType::EMPTY ? sf::Color::Transparent : BlockColor[type]);
    block->setOutline(type);
    block->content.setTexture(&Resources::BlockTextureCollection::getInstance()->Grass);
}

void GameSetting::BlockThemeSetter::applyBlockTheme(GameEntity::Block *block, GameEntity::BlockType type)
{
    switch(m_blockTheme)
    {
        case none:
            applyNone(block, type);
            break;
        case wood:
            applyWoodTexture(block, type);
            break;
        case grass:
            applyGrassTexture(block, type);
        default:
            break;
    }
}

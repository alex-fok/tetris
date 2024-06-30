#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "../Resources/BlockTextureCollection.hpp"
#include "../GameEntity/BlockType.hpp"
#include "../GameEntity/Block.hpp"
#include "BlockTheme.hpp"

namespace GameSetting
{
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

    class BlockThemeSetter
    {
    private:
        BlockTheme m_blockTheme;
        std::vector<GameEntity::Block *> m_blocks;
    public:
        BlockThemeSetter();
        void setBlockTheme(BlockTheme);
        void addBlockThemeSubscription(GameEntity::Block *);
        void applyNone(GameEntity::Block *, GameEntity::BlockType);
        void applyWoodTexture(GameEntity::Block *, GameEntity::BlockType);
        void applyGrassTexture(GameEntity::Block *, GameEntity::BlockType);
        void applyBlockTheme(GameEntity::Block *, GameEntity::BlockType);
    };
}

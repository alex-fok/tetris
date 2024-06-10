#include "Setting.hpp"

GameSetting::Setting::Setting()
{
}

void GameSetting::Setting::setBlockTheme(BlockTheme theme)
{
    m_blockThemeSetter.setBlockTheme(theme);
}

void GameSetting::Setting::applyBlockTheme(GameEntity::Block *block, GameEntity::BlockType type)
{
    m_blockThemeSetter.applyBlockTheme(block, type);
}

void GameSetting::Setting::forwarder_applyBlockTheme(Setting *self, GameEntity::Block *block, GameEntity::BlockType type)
{
    self->applyBlockTheme(block, type);
}

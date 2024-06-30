#pragma once
#include <vector>
#include "../GameEntity/Block.hpp"
#include "BlockThemeSetter.hpp"

namespace GameSetting {
    class Setting
    {
    private:
        BlockThemeSetter m_blockThemeSetter;
        
    public:
        Setting();
        void setBlockTheme(BlockTheme);
        void addBlockThemeSubscription(GameEntity::Block *);
        void applyBlockTheme(GameEntity::Block *, GameEntity::BlockType);
        static void forwarder_setBlockTheme(Setting *, BlockTheme);
        static void forwarder_applyBlockTheme(Setting *, GameEntity::Block *, GameEntity::BlockType);
    };
};

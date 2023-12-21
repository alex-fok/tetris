#pragma once
#include <vector>
#include "../GameUI/Config.hpp"
#include "TetrominoFactory.hpp"

namespace GameEntity
{
    class PreviewList
    {
    private:
        TetrominoFactory *m_tetroFactory;
    public:
        Tetromino **m_tetros;
        PreviewList(TetrominoFactory *tetroFactory);
        void update();
        static void forwarder_update(PreviewList *self);
        ~PreviewList();
    };
}

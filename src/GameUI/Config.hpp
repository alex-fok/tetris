#pragma once

namespace GameUI
{
    struct Position {
        float x, y;
    };
    struct Count {
        int x, y;
    };
    namespace Config
    {
        namespace Window
        {
            static constexpr float Width = 800.f;
            static constexpr float Height = 600.f;
        }
        namespace Menu
        {
            static constexpr float BorderWidth = 1.f;
            namespace GameOver
            {
                static constexpr float Width = 250.f;
                static constexpr float Height = 400.f;
            }
            namespace Pause
            {
                static constexpr float Width = 250.f;
                static constexpr float Height = 400.f;
            }
        }
        namespace PreviewList
        {
            static constexpr size_t Count = 4;
        }
        namespace Block
        {
            static constexpr float Size = 29.f;
        }
        namespace TetrominoContainer
        {
            static constexpr Position Offset = {250.f, 0.f};
            static constexpr Count BlockCount = {10, 20};
            static constexpr float BorderWidth = 10.f;
            static constexpr float Width = (Block::Size - 1) * BlockCount.x + BorderWidth * 2.f + 1;
            static constexpr float Height = (Block::Size - 1) * BlockCount.y + BorderWidth * 2.f + 1;
        }
    };
}

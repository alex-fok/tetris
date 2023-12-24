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
        namespace PreviewList
        {
            static constexpr Position Offset = {TetrominoContainer::Offset.x + TetrominoContainer::Width, 0.f};
            static constexpr size_t Count = 4;
            namespace Next
            {
                static constexpr float Margin_Top = 10.f;
                static constexpr float ContainerSize = 125.f;
                static constexpr float OutlineThickness = -3.f;
                static constexpr float BlockSize = 29.f;
            }
            namespace InLine
            {
                static constexpr float Margin_Top = 10.f;
                static constexpr float ContainerSize = 80.f;
                static constexpr float OutlineThickness = -1.f;
                static constexpr float BlockSize = 0.f;
            }
        }
    };
}

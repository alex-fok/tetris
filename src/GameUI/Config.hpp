#pragma once

namespace GameUI
{
    struct Position {
        float x, y;
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
        namespace TetrominoContainer
        {
            static constexpr Position Window_Offset = {250.f, 0.f};
            static constexpr float BorderWidth = 10.f;
        }
        namespace Block
        {
            static constexpr float Size = 29.f;
        }
    };
}

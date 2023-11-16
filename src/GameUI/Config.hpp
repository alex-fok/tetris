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
        namespace TetrominoContainer
        {
            static constexpr Position Window_Offset = {250.f, 0.f};
            static constexpr float BorderWidth = 10.f;
        }
    };
}

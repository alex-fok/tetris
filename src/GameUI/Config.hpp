#pragma once
#include "SFML/Graphics.hpp"

namespace GameUI
{
    struct Position { float x, y; };
    struct Count { int x, y; };
    struct Limit { float Top, Right, Bottom, Left; };
    
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
            static constexpr Count BlockCount = {10, 20};
            static constexpr float BorderWidth = 10.f;
            static constexpr float Width = (Block::Size - 1) * BlockCount.x + BorderWidth * 2.f + 1;
            static constexpr float Height = (Block::Size - 1) * BlockCount.y + BorderWidth * 2.f + 1;
            static constexpr float LineWidth = 29.f * 10 - 1.f * 9;
            static constexpr Limit PosLimit = Limit{ 0.f, 250.f + Width, Height, 250.f };
        }
        namespace Score
        {
            static constexpr Limit PosLimit = Limit{ 200.f, TetrominoContainer::PosLimit.Left, Window::Height, 0.f };
            namespace ScoreText
            {
                static constexpr float Margin_Top = 10.f;
            }
        }        
        namespace Hold
        {
            static constexpr Limit PosLimit = Limit{ 10.f, TetrominoContainer::PosLimit.Left, Window::Height, 0.f } ;
            namespace Box
            {
                static constexpr Limit PosLimit = Limit{ 10.f, TetrominoContainer::PosLimit.Left, 0.f, 0.f };
                static constexpr float ContainerSize = 120.f;
                static constexpr float OutlineThickness = 3.f;
                static constexpr float BlockSize = 29.f;
            }
        }
        namespace PreviewList
        {
            static constexpr size_t Count = 4;
            static constexpr Limit PosLimit = Limit{ 10.f, Window::Width, Window::Height, TetrominoContainer::PosLimit.Right };
            namespace Next
            {
                static constexpr float Margin_Top = 10.f;
                static constexpr float ContainerSize = 120.f;
                static constexpr float OutlineThickness = 3.f;
                static constexpr float BlockSize = 29.f;
            }
            namespace InLine
            {
                static constexpr float Margin_Top = 10.f;
                static constexpr float ContainerSize = 80.f;
                static constexpr float OutlineThickness = 1.f;
                static constexpr float BlockSize = 20.f;
            }
        }
        namespace Animation
        {
            namespace ClearLines
            {
                static constexpr float Duration = 1.f;
            }
            namespace Scoring
            {
                static constexpr float Duration = 1.f;
            }
        }
    };
}

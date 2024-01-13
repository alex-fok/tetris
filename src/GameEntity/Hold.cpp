#include "../GameUI/Config.hpp"

#include "Hold.hpp"
#include <iostream>
GameEntity::Hold::Hold(sf::RenderWindow *window) :
    Drawable(window),
    m_tetromino(0),
    m_hold(window)
{
    namespace Hold = GameUI::Config::Hold;
    
    m_hold.init(
        Hold::ContainerSize,
        { (Hold::PosLimit.Left + Hold::PosLimit.Right) / 2, Hold::ContainerSize / 2 + Hold::Margin_Top },
        Hold::OutlineThickness,
        Hold::BlockSize
    );
}

GameEntity::Tetromino *GameEntity::Hold::switchTetro(Tetromino *next)
{
    std::swap(m_tetromino, next);
    m_tetromino->resetRotation();
    m_hold.updateTetromino(m_tetromino->type);
    return next;
}

void GameEntity::Hold::render()
{
    m_hold.render();
}

GameEntity::Tetromino *GameEntity::Hold::forwarder_switchTetro(Hold *hold, Tetromino *next)
{
    return hold->switchTetro(next);
}

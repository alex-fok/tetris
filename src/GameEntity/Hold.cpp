#include "../GameUI/Config.hpp"

#include "Hold.hpp"
#include <iostream>
GameEntity::Hold::Hold(sf::RenderWindow *window) :
    Drawable(window),
    m_tetromino(0),
    m_hold(window),
    m_text(sf::Text())
{
    namespace Hold = GameUI::Config::Hold;
    namespace Box = Hold::Box;
    
    m_text.setFont(Resources::FontCollection::getInstance()->RobotoRegular);
    m_text.setString("Hold");
    auto localBounds = m_text.getLocalBounds();
    m_text.setOrigin(localBounds.width / 2, localBounds.height / 2);
    m_text.setPosition((Hold::PosLimit.Right - Hold::PosLimit.Left) / 2, localBounds.height / 2 + Hold::PosLimit.Top);
    m_text.setColor(sf::Color::White);

    m_hold.init(
        Box::ContainerSize,
        { (Box::PosLimit.Left + Box::PosLimit.Right) / 2, Box::ContainerSize / 2 + Hold::PosLimit.Top + localBounds.height + Box::PosLimit.Top },
        Box::OutlineThickness,
        Box::BlockSize
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
    draw(m_text);
}

GameEntity::Tetromino *GameEntity::Hold::forwarder_switchTetro(Hold *hold, Tetromino *next)
{
    return hold->switchTetro(next);
}

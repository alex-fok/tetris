#include "PreviewList.hpp"
#include "../GameUI/Config.hpp"
#include "Block.hpp"

#include <iostream>

const sf::Vector2f GameEntity::PreviewList::relativePos[Tetromino::TypeCount][Tetromino::BlockCount] = {
    // I
    {{-2, -.5}, {-1, -.5}, {0, -.5}, {1, -.5}},
    // O
    {{-1, -1}, {0, -1}, {-1, 0}, {0, 0}},
    // T
    {{-1.5, 0}, {-.5, 0}, {.5, 0}, {-.5, -1}},
    // J
    {{-1.5, 0}, {-1.5, -1}, {-.5, 0}, {.5, 0}},
    // L
    {{-1.5, 0}, {-.5, 0}, {.5, 0}, {.5, -1}},
    // S
    {{-1.5, 0}, {-.5, 0}, {-.5, -1}, {.5, -1}},
    // Z
    {{-1.5, -1}, {-.5, 0}, {-.5, -1}, {.5, 0}}
};

GameEntity::PreviewList::PreviewList(sf::RenderWindow *window, TetrominoFactory *tetroFactory) :
    Drawable(window),
    m_tetroFactory(tetroFactory),
    m_tetros(new Tetromino *[GameUI::Config::PreviewList::Count])
{
    tetroFactory->peek(GameUI::Config::PreviewList::Count, m_tetros);
    m_tetroFactory->addSubscription(std::bind(forwarder_update, this));

    namespace Next = GameUI::Config::PreviewList::Next;
    auto offset = GameUI::Config::PreviewList::Offset;
    // m_next
    m_nextContainer.setSize({Next::ContainerSize, Next::ContainerSize});
    m_nextContainer.setOrigin({Next::ContainerSize / 2, Next::ContainerSize / 2});
    m_nextContainer.setPosition({
        offset.x + (GameUI::Config::Window::Width - offset.x) / 2,
        Next::ContainerSize / 2 + Next::Margin_Top
    });
    m_nextContainer.setOutlineThickness(Next::OutlineThickness * -1.f);
    m_nextContainer.setOutlineColor(sf::Color::White);
    m_nextContainer.setFillColor(sf::Color::Transparent);

    for (size_t i = 0; i < Tetromino::BlockCount; ++i)
        m_next_blocks[i].setSize({GameUI::Config::PreviewList::Next::BlockSize, GameUI::Config::PreviewList::Next::BlockSize});
    
    // m_inLine
    namespace InLine = GameUI::Config::PreviewList::InLine;
    auto topContainerPosY = Next::Margin_Top + Next::ContainerSize + InLine::Margin_Top + InLine::ContainerSize / 2;
    for (size_t i = 0; i < GameUI::Config::PreviewList::Count - 1; ++i)
    {
        // Container
        m_inLineContainer[i].setSize({InLine::ContainerSize, InLine::ContainerSize});
        m_inLineContainer[i].setOrigin({InLine::ContainerSize / 2, InLine::ContainerSize / 2});
        m_inLineContainer[i].setPosition({
            offset.x + (GameUI::Config::Window::Width - offset.x) / 2,
            topContainerPosY + InLine::ContainerSize * i + InLine::Margin_Top * i
        });
        m_inLineContainer[i].setOutlineThickness(InLine::OutlineThickness * -1.f);
        m_inLineContainer[i].setOutlineColor(sf::Color::White);
        m_inLineContainer[i].setFillColor(sf::Color::Transparent);

        // Blocks
        for (size_t j = 0; j < Tetromino::BlockCount; ++j)
            m_inLine_blocks[i][j].setSize({GameUI::Config::PreviewList::InLine::BlockSize, GameUI::Config::PreviewList::InLine::BlockSize});
    }
}

void GameEntity::PreviewList::update()
{
    m_tetroFactory->peek(GameUI::Config::PreviewList::Count, m_tetros);
    // Reset
    for (size_t i = 0; i < Tetromino::BlockCount; ++i)
        for (size_t j = 0; j < GameUI::Config::PreviewList::Count - 1; ++j) 
        {
            m_next_blocks[i].reset();
            m_inLine_blocks[j][i].reset();
        }
    // Place Tetromino
    // Next
    auto nextCenter = m_nextContainer.getPosition();
    // Finish next center
    auto nextVectors = relativePos[m_tetros[0]->type];
    for (size_t i = 0; i < Tetromino::BlockCount; ++i)
    {
        m_next_blocks[i].setPosition(
            nextCenter.x + 29.f * nextVectors[i].x,
            nextCenter.y + 29.f * nextVectors[i].y
        );
        m_next_blocks[i].setTetromino(-1, m_tetros[0]->type);
    }
    // Tetros In line
    for (size_t i = 0; i < GameUI::Config::PreviewList::Count - 1; ++i)
    {
        auto inLineCenter = m_inLineContainer[i].getPosition();
        auto inLineVectors = relativePos[m_tetros[i + 1]->type];
        for (size_t j = 0; j < Tetromino::BlockCount; ++j)
        {
            m_inLine_blocks[i][j].setPosition(
                inLineCenter.x + 20.f * inLineVectors[j].x,
                inLineCenter.y + 20.f * inLineVectors[j].y
            );
            m_inLine_blocks[i][j].setTetromino(-1, m_tetros[i + 1]->type);
        }
    }
}

void GameEntity::PreviewList::forwarder_update(PreviewList *self)
{
    self->update();
}

void GameEntity::PreviewList::render()
{
    for (size_t i = 0; i < Tetromino::BlockCount; ++i)
        draw(m_next_blocks[i].content);
        
    draw(m_nextContainer);
    for (size_t i = 0; i < GameUI::Config::PreviewList::Count - 1; ++i)
    {
        for (size_t j = 0; j < Tetromino::BlockCount; ++j)
            draw(m_inLine_blocks[i][j].content);
        draw(m_inLineContainer[i]);
    }
}

GameEntity::PreviewList::~PreviewList()
{
    delete(m_tetros);
}

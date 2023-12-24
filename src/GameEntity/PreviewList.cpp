#include "PreviewList.hpp"
#include "../GameUI/Config.hpp"
#include "Block.hpp"

#include <iostream>

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
    m_next.setSize({Next::ContainerSize, Next::ContainerSize});
    m_next.setOrigin({Next::ContainerSize / 2, Next::ContainerSize / 2});
    m_next.setPosition({offset.x + (GameUI::Config::Window::Width - offset.x) / 2, Next::ContainerSize / 2 + Next::Margin_Top});
    m_next.setOutlineThickness(Next::OutlineThickness * -1.f);
    m_next.setOutlineColor(sf::Color::White);
    m_next.setFillColor(sf::Color::Transparent);

    GameUI::Position startPos = {
        offset.x + (GameUI::Config::Window::Width - offset.x)/2 - Next::ContainerSize / 2 + Next::OutlineThickness,
        Next::Margin_Top + Next::OutlineThickness
    };

    for (size_t i = 0; i < 4; ++i)
    {
        auto reverse_i = 4 - i - 1;
        for (size_t j = 0; j < 4; ++j)
        {
            m_next_blocks[i][j].setSize({29.f, 29.f});
            m_next_blocks[i][j].setPosition(
                startPos.x + GameUI::Config::Block::Size * j - j,
                startPos.y + GameUI::Config::Block::Size * reverse_i - reverse_i
            );
        }
    }

    // m_inLine
    namespace InLine = GameUI::Config::PreviewList::InLine;
    auto topContainerPosY = Next::Margin_Top + Next::ContainerSize + InLine::Margin_Top + InLine::ContainerSize / 2;
    for (size_t i = 0; i < GameUI::Config::PreviewList::Count - 1; ++i)
    {
        // Container
        m_inLine[i].setSize({InLine::ContainerSize, InLine::ContainerSize});
        m_inLine[i].setOrigin({InLine::ContainerSize / 2, InLine::ContainerSize / 2});
        m_inLine[i].setPosition({
            offset.x + (GameUI::Config::Window::Width - offset.x) / 2,
            topContainerPosY + InLine::ContainerSize * i + InLine::Margin_Top * i
        });
        m_inLine[i].setOutlineThickness(InLine::OutlineThickness * -1.f);
        m_inLine[i].setOutlineColor(sf::Color::White);
        m_inLine[i].setFillColor(sf::Color::Transparent);

        // Blocks
        GameUI::Position topBlockPos = {
            offset.x + (GameUI::Config::Window::Width - offset.x)/2 - InLine::ContainerSize / 2 + InLine::OutlineThickness,
            Next::Margin_Top + Next::ContainerSize + InLine::Margin_Top + InLine::OutlineThickness
        };
        for (size_t j = 0; j < 4; ++j)
        {
            auto reverse_j = 4 - j - 1;
            for (size_t k = 0; k < 4; ++k)
            {
                m_inLine_blocks[i][j][k].setSize({20.f, 20.f});
                m_inLine_blocks[i][j][k].setPosition(
                    topBlockPos.x + 20.f * k - k,
                    topBlockPos.y + InLine::ContainerSize * i + 20.f * reverse_j - reverse_j + InLine::Margin_Top * i + InLine::OutlineThickness * i
                );
            }
        }    
    }
}

void GameEntity::PreviewList::update()
{
    m_tetroFactory->peek(GameUI::Config::PreviewList::Count, m_tetros);
}

void GameEntity::PreviewList::forwarder_update(PreviewList *self)
{
    self->update();
}

void GameEntity::PreviewList::render()
{
    for (size_t i = 0; i < 4; ++i)
        for (size_t j = 0; j < 4; ++j)
            draw(m_next_blocks[j][i].content);
        
    draw(m_next);
    for (size_t i = 0; i < GameUI::Config::PreviewList::Count - 1; ++i)
    {
        for (size_t j = 0; j < 4; ++j)
            for (size_t k = 0; k < 4; ++k)
                draw(m_inLine_blocks[i][j][k].content);
        draw(m_inLine[i]);
    }
}

GameEntity::PreviewList::~PreviewList()
{
    delete(m_tetros);
}

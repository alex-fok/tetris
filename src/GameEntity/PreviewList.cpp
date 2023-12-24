#include "PreviewList.hpp"
#include "../GameUI/Config.hpp"
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
    m_next.setOutlineThickness(Next::OutlineThickness);
    m_next.setOutlineColor(sf::Color::White);
    m_next.setFillColor(sf::Color::Transparent);

    // m_inLine
    namespace InLine = GameUI::Config::PreviewList::InLine;
    auto topPosY = Next::Margin_Top + Next::ContainerSize + InLine::Margin_Top + InLine::ContainerSize / 2;
    for (size_t i = 0; i < GameUI::Config::PreviewList::Count - 1; ++i)
    {
        m_inLine[i].setSize({InLine::ContainerSize, InLine::ContainerSize});
        m_inLine[i].setOrigin({InLine::ContainerSize / 2, InLine::ContainerSize / 2});
        m_inLine[i].setPosition({
            offset.x + (GameUI::Config::Window::Width - offset.x) / 2,
            topPosY + InLine::ContainerSize * i + InLine::Margin_Top * i
        });
        m_inLine[i].setOutlineThickness(InLine::OutlineThickness);
        m_inLine[i].setOutlineColor(sf::Color::White);
        m_inLine[i].setFillColor(sf::Color::Transparent);
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
    draw(m_next);
    for (size_t i = 0; i < GameUI::Config::PreviewList::Count - 1; ++i)
        draw(m_inLine[i]);
}

GameEntity::PreviewList::~PreviewList()
{
    delete(m_tetros);
}

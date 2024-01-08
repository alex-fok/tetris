#include "PreviewList.hpp"
#include "../GameUI/Config.hpp"
#include "Block.hpp"

GameEntity::PreviewList::PreviewList(sf::RenderWindow *window, TetrominoFactory *tetroFactory) :
    Drawable(window),
    m_tetroFactory(tetroFactory),
    m_tetros(new Tetromino *[GameUI::Config::PreviewList::Count]),
    m_next(window)
{
    m_tetroFactory->addSubscription(std::bind(forwarder_update, this));

    namespace Next = GameUI::Config::PreviewList::Next;
    auto offset = GameUI::Config::PreviewList::Offset;
    
    m_next.init(
        Next::ContainerSize,
        { offset.x + (GameUI::Config::Window::Width - offset.x) / 2, Next::ContainerSize / 2 + Next::Margin_Top },
        Next::OutlineThickness,
        Next::BlockSize
    );
    
    namespace InLine = GameUI::Config::PreviewList::InLine;
    auto topContainerPosY = Next::Margin_Top + Next::ContainerSize + InLine::Margin_Top + InLine::ContainerSize / 2;
    for (size_t i = 0; i < GameUI::Config::PreviewList::Count - 1; ++i)
    {
        m_inLine[i] = GameEntity::SingleTetroBox(window);
        m_inLine[i].init(
            InLine::ContainerSize,
            { offset.x + (GameUI::Config::Window::Width - offset.x) / 2, topContainerPosY + InLine::ContainerSize * i + InLine::Margin_Top * i },
            InLine::OutlineThickness,
            InLine::BlockSize
        );
    }
}

void GameEntity::PreviewList::update()
{
    m_tetroFactory->peek(GameUI::Config::PreviewList::Count, m_tetros);
    m_next.reset();
    m_next.updateTetromino(m_tetros[0]->type);
    for (size_t i = 0; i < Tetromino::BlockCount - 1; ++i)
    {
        m_inLine[i].reset();
        m_inLine[i].updateTetromino(m_tetros[i + 1]->type);
    }
}

void GameEntity::PreviewList::forwarder_update(PreviewList *self)
{
    self->update();
}

void GameEntity::PreviewList::render()
{
    m_next.render();
    for (size_t i = 0; i < GameUI::Config::PreviewList::Count - 1; ++i)
        m_inLine[i].render();
}

GameEntity::PreviewList::~PreviewList()
{
    delete(m_tetros);
}

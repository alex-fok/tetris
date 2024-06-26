#include "PreviewList.hpp"
#include "../GameUI/Config.hpp"
#include "Block.hpp"
#include "iostream"

GameEntity::PreviewList::PreviewList(sf::RenderWindow *window, TetrominoFactory *tetroFactory, GameSetting::Setting *setting) :
    Drawable(window),
    m_tetroFactory(tetroFactory),
    m_tetros(new Tetromino *[GameUI::Config::PreviewList::Count]),
    m_next(window, setting),
    m_text(sf::Text())
{
    m_tetroFactory->addSubscription(std::bind(forwarder_update, this));

    namespace Next = GameUI::Config::PreviewList::Next;
    auto limit = GameUI::Config::PreviewList::PosLimit;

    m_text.setFont(Resources::FontCollection::getInstance()->RobotoRegular);
    m_text.setString("Next");
    auto localBounds = m_text.getLocalBounds();
    
    m_text.setOrigin(localBounds.width / 2, localBounds.height / 2);
    m_text.setPosition((limit.Right + limit.Left) / 2, limit.Top + localBounds.height / 2);
    m_text.setFillColor(sf::Color::White);

    m_next.init(
        Next::ContainerSize,
        { (limit.Left + limit.Right) / 2, limit.Top + localBounds.height + Next::Margin_Top + Next::ContainerSize / 2 },
        Next::OutlineThickness,
        Next::BlockSize
    );

    namespace InLine = GameUI::Config::PreviewList::InLine;
    auto topContainerPosY = limit.Top + localBounds.height + Next::Margin_Top + Next::ContainerSize + InLine::Margin_Top + InLine::ContainerSize / 2;
    for (size_t i = 0; i < GameUI::Config::PreviewList::Count - 1; ++i)
    {
        m_inLine[i] = GameEntity::SingleTetroBox(window, setting);
        m_inLine[i].init(
            InLine::ContainerSize,
            { limit.Left + (GameUI::Config::Window::Width - limit.Left) / 2, topContainerPosY + InLine::ContainerSize * i + InLine::Margin_Top * i },
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
    draw(m_text);
}

GameEntity::PreviewList::~PreviewList()
{
    delete(m_tetros);
}

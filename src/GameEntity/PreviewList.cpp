#include "PreviewList.hpp"
#include "../GameUI/Config.hpp"
#include <iostream>

GameEntity::PreviewList::PreviewList(TetrominoFactory *tetroFactory) :
    m_tetroFactory(tetroFactory)
{
    tetroFactory->peek(GameUI::Config::PreviewList::Count, m_tetros);
    m_tetroFactory->addSubscription(std::bind(forwarder_update, this));
}
void GameEntity::PreviewList::update()
{
    m_tetroFactory->peek(GameUI::Config::PreviewList::Count, m_tetros);
}

void GameEntity::PreviewList::forwarder_update(PreviewList *self)
{
    self->update();
}

GameEntity::PreviewList::~PreviewList()
{
    delete(m_tetros);
}

#include "SingleTetroBox.hpp"

const sf::Vector2f GameEntity::SingleTetroBox::relativePos[Tetromino::TypeCount][Tetromino::BlockCount] =
{
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

GameEntity::SingleTetroBox::SingleTetroBox()
{
}

GameEntity::SingleTetroBox::SingleTetroBox(sf::RenderWindow *window) :
    Drawable(window)
{
}

void GameEntity::SingleTetroBox::init(float size, sf::Vector2f pos, float outlineThickness, float tetroBlockSize)
{
    m_blockSize = tetroBlockSize;
    m_pos = pos;
    m_box.setSize({size, size});
    m_box.setOrigin(size / 2, size / 2);
    m_box.setPosition(pos);
    m_box.setOutlineThickness(outlineThickness * -1.f);
    m_box.setOutlineColor(sf::Color::White);
    m_box.setFillColor(sf::Color::Transparent);

    for (size_t i = 0; i < Tetromino::BlockCount; ++i)
    {
        m_blocks[i].setSize({tetroBlockSize, tetroBlockSize});
        m_blocks[i].setOutline({BlockType::EMPTY});
    }
}

void GameEntity::SingleTetroBox::updateTetromino(GameEntity::BlockType type)
{
    auto vectors = relativePos[type];
    for (size_t i = 0; i < Tetromino::BlockCount; ++i)
    {
        m_blocks[i].setPosition(m_pos.x + m_blockSize * vectors[i].x, m_pos.y + m_blockSize * vectors[i].y);
        m_blocks[i].setTetromino(-1, type);
    }
}

void GameEntity::SingleTetroBox::reset()
{
    for (size_t i = 0; i < Tetromino::BlockCount; ++i)
        m_blocks[i].reset();
}

void GameEntity::SingleTetroBox::render()
{
    draw(m_box);
    for (size_t i = 0; i < Tetromino::BlockCount; ++i)
        draw(m_blocks[i].content);
}

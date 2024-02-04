#include "Tetromino.hpp"
const GameEntity::Vector GameEntity::Tetromino::Type[TypeCount][RotationCount][BlockCount] =
{
    // I
    {
        {{0, 2}, {1, 2}, {2, 2}, {3, 2}},
        {{2, 0}, {2, 1}, {2, 2}, {2, 3}},
        {{0, 1}, {1, 1}, {2, 1}, {3, 1}},
        {{1, 0}, {1, 1}, {1, 2}, {1, 3}}
    },
    // O
    {
        {{1, 2}, {2, 2}, {1, 3}, {2, 3}},
        {{1, 2}, {2, 2}, {1, 3}, {2, 3}},
        {{1, 2}, {2, 2}, {1, 3}, {2, 3}},
        {{1, 2}, {2, 2}, {1, 3}, {2, 3}}
    },
    // T
    {
        {{0, 2}, {1, 2}, {2, 2}, {1, 3}},
        {{1, 1}, {1, 2}, {2, 2}, {1, 3}},
        {{1, 1}, {0, 2}, {1, 2}, {2, 2}},
        {{1, 1}, {0, 2}, {1, 2}, {1, 3}}
    },
    // J
    {
        {{0, 3}, {0, 2}, {1, 2}, {2, 2}},
        {{1, 1}, {1, 2}, {1, 3}, {2, 3}},
        {{2, 1}, {0, 2}, {1, 2}, {2, 2}},
        {{0, 1}, {1, 1}, {1, 2}, {1, 3}}
    },
    // L
    {
        {{0, 2}, {1, 2}, {2, 2}, {2, 3}},
        {{1, 1}, {2, 1}, {1, 2}, {1, 3}},
        {{0, 1}, {0, 2}, {1, 2}, {2, 2}},
        {{1, 1}, {1, 2}, {0, 3}, {1, 3}}
    },
    // S
    {
        {{0, 2}, {1, 2}, {1, 3}, {2, 3}},
        {{2, 1}, {1, 2}, {2, 2}, {1, 3}},
        {{0, 1}, {1, 1}, {1, 2}, {2, 2}},
        {{1, 1}, {0, 2}, {1, 2}, {0, 3}}
    },
    // Z
    {
        {{1, 2}, {2, 2}, {0, 3}, {1, 3}},
        {{1, 1}, {1, 2}, {2, 2}, {2, 3}},
        {{1, 1}, {2, 1}, {0, 2}, {1, 2}},
        {{0, 1}, {0, 2}, {1, 2}, {1, 3}},
    }
};

const GameEntity::Vector GameEntity::Tetromino::WallKick_Offset[RotationCount][DirectionCount][TestCount] =
{   // Rotation tests for all Tetrominoes except I
    // 0 = 0 degree, 1 = 90 degree, 2 = 180 degree, 3 = 270 degree, clockwise
    // 1 >> 2 implies a clockwise rotation from 90 to 180 degree; Likewise,
    // 3 >> 2 implies a counter clockwise rotation from 270 to 180 degree
    {
        // 0 >> 1
        {{0, 0}, {-1, 0}, {-1, 1}, {0, 2}, {-1, -2}},
        // 0 >> 3
        {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}}
    },
    {   
        // 1 >> 2
        {{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}},
        // 1 >> 0
        {{0, 0}, {1, 0}, {1, -1}, {0, 2}, {1, 2}},
    },
    {
        // 2 >> 3
        {{0, 0}, {1, 0}, {1, 1}, {0, -2}, {1, -2}},
        // 2 >> 1
        {{0, 0}, {-1, 0}, {-1, 1}, {0, -2}, {-1, -2}}
    },
    {
        // 3 >> 0
        {{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}},
        // 3 >> 2
        {{0, 0}, {-1, 0}, {-1, -1}, {0, 2}, {-1, 2}}
    }
};

const GameEntity::Vector GameEntity::Tetromino::WallKick_Offset_I[RotationCount][DirectionCount][TestCount] =
{   // Rotation tests for I only
    {
        // 0 >> 1
        {{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}},
        // 0 >> 3
        {{0, 0}, {-1, 0}, {2, 0}, {-1, 2}, {2, -1}}
    },
    {
        // 1 >> 2
        {{0, 0}, {-1, 0}, {2, 0}, {-1, 2}, {2, -1}},
        // 1 >> 0
        {{0, 0}, {2, 0}, {-1, 0}, {2, 1}, {-1, -2}}
    },
    {
        // 2 >> 3
        {{0, 0}, {2, 0}, {-1, 0}, {2, 1}, {-1, -2}},
        // 2 >> 1
        {{0, 0}, {1, 0}, {-2, 0}, {1, -2}, {-2, 1}}
    },
    {
        // 3 >> 0
        {{0, 0}, {1, 0}, {-2, 0}, {1, -2}, {-2, 1}},
        // 3 >> 2
        {{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}}
    }
};

GameEntity::Tetromino::Tetromino(int id, BlockType b_type) :
    m_rotation(0), type(b_type), id(id), position(Type[b_type][0])
{
}

const GameEntity::Vector * GameEntity::Tetromino::getWallKickOffsets(Rotation r)
{
    return type != I ? WallKick_Offset[m_rotation][r] : WallKick_Offset_I[m_rotation][r];
}

const GameEntity::Vector * GameEntity::Tetromino::peek(Rotation r)
{
    return Tetromino::Type[type][(r == Clockwise ? m_rotation + 1 : m_rotation - 1) % 4];
}

void GameEntity::Tetromino::rotate(Rotation r)
{
    m_rotation = r == Clockwise ? (m_rotation + 1) % 4 : (m_rotation - 1 + 4) % 4;
    position = Tetromino::Type[type][m_rotation];
}

void GameEntity::Tetromino::resetRotation()
{
    m_rotation = 0;
    position = Tetromino::Type[type][m_rotation];
}

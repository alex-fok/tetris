#pragma once
#include "Vector.hpp"
#include "Block.hpp"

namespace GameEntity
{
    class Tetromino
    {
    private:
        int m_rotation;
    public:
        enum Rotation
        {
            Clockwise, CounterClockwise
        };

        // Number of types of Tetromino; I, O, T, J, L, S, Z
        static const int TypeCount = 7;

        // Number of rotated positions; 0, 90, 180, 270 degrees
        static const int RotationCount = 4;

        // Number of blocks in each Tetromino
        static const int BlockCount = 4;

        // Number of rotation direction; Clockwise, Counter Clockwise
        static const int DirectionCount = 2;

        // Number of offset test when performing a rotation
        static const int TestCount = 5;

        // Array of Tetrominoes and their rotated positions, each represented in a set of 4 Vectors
        static const Vector Type[TypeCount][RotationCount][BlockCount];

        // Array of offsets for wallkick, separated by their respective rotated positions, rotate direction 
        const static Vector WallKick_Offset[RotationCount][DirectionCount][TestCount];

        // Array of offsets for I's wallkick, separated by their respective rotated positions, rotate direction 
        const static Vector WallKick_Offset_I[RotationCount][DirectionCount][TestCount];
        
        
        int id;
        BlockType type;
        const Vector *position;
        Tetromino(int id, BlockType b_type);
        const Vector * getWallKickOffsets(Rotation);
        const Vector * peek(Rotation);
        void rotate(Rotation);
        void resetRotation();
    };
};

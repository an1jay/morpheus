#include <stdint.h>

#pragma once

// Defining the various squares on the board
enum class Square : int
{
    // clang-format off
    A1, B1, C1, D1, E1, F1, G1, H1,
    A2, B2, C2, D2, E2, F2, G2, H2,
    A3, B3, C3, D3, E3, F3, G3, H3,
    A4, B4, C4, D4, E4, F4, G4, H4,
    A5, B5, C5, D5, E5, F5, G5, H5,
    A6, B6, C6, D6, E6, F6, G6, H6,
    A7, B7, C7, D7, E7, F7, G7, H7,
    A8, B8, C8, D8, E8, F8, G8, H8,
    NONE,
    // clang-format on
};

// Defining the various files on the board
enum class File : int
{
    // clang-format off
    FA, FB, FC, FD, FE, FF, FG, H,
    NONE,
    // clang-format on
};

// Defining the various ranks on the board
enum class Rank : int
{
    // clang-format off
    R1, R2, R3, R4, R5, R6, R7, R8,
    RNONE,
    // clang-format on
};

// Defining the various pieces
enum class Piece : int
{
    // clang-format off
    W_PAWN = 1, W_KNIGHT, W_BISHOP, W_ROOK, W_QUEEN, W_KING,
    B_PAWN = 9, B_KNIGHT, B_BISHOP, B_ROOK, B_QUEEN, B_KING,
    PIECE_NONE = 16,
    // clang-format on
};

// Defining the various piece types
enum class PieceType : int
{
    // clang-format off
    PAWN, KNIGHT, BISHOOP, ROOK, QUEEN, KING,
    // clang-format on
};

// Defining the various colors
enum class Color : int
{
    COLOR_WHITE = 1,
    COLOR_BLACK = -1,
    COLOR_NONE = 0,
};
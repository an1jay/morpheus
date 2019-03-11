#include <stdint.h>

#pragma once

// Defining the various squares on the board
enum class Square : int_fast8_t
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
enum class File : int_fast8_t
{
    // clang-format off
    FA, FB, FC, FD, FE, FF, FG, H,
    NONE,
    // clang-format on
};

// Defining the various ranks on the board
enum class Rank : int_fast8_t
{
    // clang-format off
    R1, R2, R3, R4, R5, R6, R7, R8,
    RNONE,
    // clang-format on
};

// Defining the various pieces
enum class Piece : int_fast8_t
{
    // clang-format off
    W_PAWN = 1, W_KNIGHT, W_BISHOP, W_ROOK, W_QUEEN, W_KING,
    B_PAWN = 9, B_KNIGHT, B_BISHOP, B_ROOK, B_QUEEN, B_KING,
    PIECE_NONE = 15,
    // clang-format on
};

// Defining the various piece types
enum class PieceType : int_fast8_t
{
    // clang-format off
    PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING,
    // clang-format on
};

// Defining the various colors
enum class Color : int_fast8_t
{
    WHITE = 1,
    BLACK = 2,
    COLOR_NONE = 0,
};

inline Color ColorFromPiece(Piece p)
{
    if (p == Piece::PIECE_NONE)
        return Color::COLOR_NONE;
    if ((int)p < 9)
    {
        return Color::WHITE;
    }
    return Color::BLACK;
}

inline Piece PieceFromTypeColor(PieceType pt, Color c)
{
    switch (c)
    {
    case Color::BLACK:
        switch (pt)
        {
        case PieceType::PAWN:
            return Piece::B_PAWN;
        case PieceType::KNIGHT:
            return Piece::B_KNIGHT;
        case PieceType::BISHOP:
            return Piece::B_BISHOP;
        case PieceType::ROOK:
            return Piece::B_ROOK;
        case PieceType::QUEEN:
            return Piece::B_QUEEN;
        case PieceType::KING:
            return Piece::B_KING;
        }
        break;
    case Color::WHITE:
        switch (pt)
        {
        case PieceType::PAWN:
            return Piece::W_PAWN;
        case PieceType::KNIGHT:
            return Piece::W_KNIGHT;
        case PieceType::BISHOP:
            return Piece::W_BISHOP;
        case PieceType::ROOK:
            return Piece::W_ROOK;
        case PieceType::QUEEN:
            return Piece::W_QUEEN;
        case PieceType::KING:
            return Piece::W_KING;
        }
        break;
    default:
        return Piece::PIECE_NONE;
        break;
    }
}

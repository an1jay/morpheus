#include "position.h"
#include "bitboard.h"
#include "constants.h"
#include <iostream>

Position::~Position() {}

Position::Position()
{
    // clang-format off
    Piece newGamePos[64] = {
        Piece::W_ROOK, Piece::W_KNIGHT, Piece::W_BISHOP, Piece::W_QUEEN, Piece::W_KING, Piece::W_BISHOP, Piece::W_KNIGHT, Piece::W_ROOK,
        Piece::W_PAWN, Piece::W_PAWN, Piece::W_PAWN, Piece::W_PAWN, Piece::W_PAWN, Piece::W_PAWN, Piece::W_PAWN, Piece::W_PAWN, 
        Piece::PIECE_NONE, Piece::PIECE_NONE, Piece::PIECE_NONE, Piece::PIECE_NONE, Piece::PIECE_NONE, Piece::PIECE_NONE, Piece::PIECE_NONE, Piece::PIECE_NONE,
        Piece::PIECE_NONE, Piece::PIECE_NONE, Piece::PIECE_NONE, Piece::PIECE_NONE, Piece::PIECE_NONE, Piece::PIECE_NONE, Piece::PIECE_NONE, Piece::PIECE_NONE, 
        Piece::PIECE_NONE, Piece::PIECE_NONE, Piece::PIECE_NONE, Piece::PIECE_NONE, Piece::PIECE_NONE, Piece::PIECE_NONE, Piece::PIECE_NONE, Piece::PIECE_NONE,
        Piece::PIECE_NONE, Piece::PIECE_NONE, Piece::PIECE_NONE, Piece::PIECE_NONE, Piece::PIECE_NONE, Piece::PIECE_NONE, Piece::PIECE_NONE, Piece::PIECE_NONE,
        Piece::B_PAWN, Piece::B_PAWN, Piece::B_PAWN, Piece::B_PAWN, Piece::B_PAWN, Piece::B_PAWN, Piece::B_PAWN, Piece::B_PAWN,
        Piece::B_ROOK, Piece::B_KNIGHT, Piece::B_BISHOP, Piece::B_QUEEN, Piece::B_KING, Piece::B_BISHOP, Piece::B_KNIGHT, Piece::B_ROOK,
    };
    // clang-format on
    PieceList = MailBox(newGamePos);
    UpdateBitBoards();
}

void Position::UpdateBitBoards()
{
    Piece p;
    for (int sq = 0; sq < NUM_SQUARES_BOARD; ++sq)
    {
        p = PieceList.Occupation((Square)sq);
        switch (p)
        {
        case Piece::W_PAWN:
        case Piece::B_PAWN:
            Pawns ^= BBgenerate((Square)sq);
            if (PieceColor(p) == Color::COLOR_WHITE)
                WhitePieces ^= BBgenerate((Square)sq);
            else
                BlackPieces ^= BBgenerate((Square)sq);
            break;
        case Piece::W_KNIGHT:
        case Piece::B_KNIGHT:
            Knights ^= BBgenerate((Square)sq);
            if (PieceColor(p) == Color::COLOR_WHITE)
                WhitePieces ^= BBgenerate((Square)sq);
            else
                BlackPieces ^= BBgenerate((Square)sq);
            break;
        case Piece::W_BISHOP:
        case Piece::B_BISHOP:
            Bishops ^= BBgenerate((Square)sq);
            if (PieceColor(p) == Color::COLOR_WHITE)
                WhitePieces ^= BBgenerate((Square)sq);
            else
                BlackPieces ^= BBgenerate((Square)sq);
            break;
        case Piece::W_ROOK:
        case Piece::B_ROOK:
            Rooks ^= BBgenerate((Square)sq);
            if (PieceColor(p) == Color::COLOR_WHITE)
                WhitePieces ^= BBgenerate((Square)sq);
            else
                BlackPieces ^= BBgenerate((Square)sq);
            break;
        case Piece::W_QUEEN:
        case Piece::B_QUEEN:
            Queens ^= BBgenerate((Square)sq);
            if (PieceColor(p) == Color::COLOR_WHITE)
                WhitePieces ^= BBgenerate((Square)sq);
            else
                BlackPieces ^= BBgenerate((Square)sq);
            break;
        case Piece::W_KING:
        case Piece::B_KING:
            Kings ^= BBgenerate((Square)sq);
            if (PieceColor(p) == Color::COLOR_WHITE)
                WhitePieces ^= BBgenerate((Square)sq);
            else
                BlackPieces ^= BBgenerate((Square)sq);
            break;
        default:
            break;
        }
    }
}

BitBoard Position::BBForPiece(const Piece p) const
{
    switch (p)
    {
    case Piece::W_PAWN:
        return Pawns & WhitePieces;
    case Piece::W_KNIGHT:
        return Knights & WhitePieces;
    case Piece::W_BISHOP:
        return Bishops & WhitePieces;
    case Piece::W_ROOK:
        return Rooks & WhitePieces;
    case Piece::W_QUEEN:
        return Queens & WhitePieces;
    case Piece::W_KING:
        return Kings & WhitePieces;

    case Piece::B_PAWN:
        return Pawns & BlackPieces;
    case Piece::B_KNIGHT:
        return Knights & BlackPieces;
    case Piece::B_BISHOP:
        return Bishops & BlackPieces;
    case Piece::B_ROOK:
        return Rooks & BlackPieces;
    case Piece::B_QUEEN:
        return Queens & BlackPieces;
    case Piece::B_KING:
        return Kings & BlackPieces;

    default:
        return BB_NoSquares;
    }
}

void Position::Display() const
{
    for (int r = NUM_RANKS - 1; r >= 0; --r)
    {
        std::cout << std::endl
                  << "  |---|---|---|---|---|---|---|---|" << std::endl;
        std::cout << 1 + r << " |";
        for (int sq = 0; sq < NUM_SQUARES_LINE; ++sq)
        {
            std::cout << " " << PieceChars[(int)PieceList.Occupation((Square)(r * NUM_SQUARES_LINE + sq))] << " |";
        }
    }
    std::cout << std::endl
              << "  |---|---|---|---|---|---|---|---|" << std::endl
              << std::endl
              << "    A   B   C   D   E   F   G   H" << std::endl
              << std::endl;
}

Piece Position::pieceAtSquare(Square sq)
{
    return PieceList.Occupation(sq);
}
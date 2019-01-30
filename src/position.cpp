#include "position.h"
#include "bitboard.h"
#include "constants.h"

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
}

Piece Position::pieceAtSquare(Square sq)
{
    BitBoard sqBB = generateBitBoard(sq);
    if ((sqBB & WhitePieces) == BB_NoSquares || (sqBB & BlackPieces) == BB_NoSquares)
    {
        return Piece::PIECE_NONE;
    }
    else
    {
        for (int i = 0; i < NUM_PIECES; i++)
        {
            /* code */
        }
    }
    return Piece::PIECE_NONE;
}
#include "bitboard.h"
#include "primitives.h"

#pragma once

class Position
{
  private:
    BitBoard Pawns;
    BitBoard Knights;
    BitBoard Bishops;
    BitBoard Rooks;
    BitBoard Queens;
    BitBoard Kings;
    BitBoard WhitePieces;
    BitBoard BlackPieces;

    Piece pieceAtSquare(Square sq);           // Returns the piece at a square
    BitBoard BBForPiece(const Piece p) const; // Returns a bitboard for a piece

  public:
    Position(BitBoard pawns, BitBoard knights, BitBoard bishops,
             BitBoard rooks, BitBoard queens, BitBoard kings,
             BitBoard whitePieces, BitBoard blackPieces)
        : Pawns(pawns), Knights(knights), Bishops(bishops),
          Rooks(rooks), Queens(queens), Kings(kings),
          WhitePieces(whitePieces), BlackPieces(blackPieces){};

    ~Position();

    void Display() const;
};

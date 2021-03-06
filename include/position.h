#pragma once

#include "bitboard.h"
#include "magics.h"
#include "mailbox.h"

#include "primitives.h"
#include <vector>

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
    BitBoard Occupancy; // TODO to be checked if faster

    MailBox PieceList;
    Color ColorToMove;

    Piece pieceAtSquare(Square sq);           // Returns the piece at a square
    BitBoard BBForPiece(const Piece p) const; // Returns a bitboard for a piece
    void SyncBBfromPieceList();               // update bitboards from the mailbox

  public:
    Position(); // Makes new game position
    Position(const Position &p);

    Position(BitBoard pawns, BitBoard knights, BitBoard bishops,
             BitBoard rooks, BitBoard queens, BitBoard kings,
             BitBoard whitePieces, BitBoard blackPieces)
        : Pawns(pawns), Knights(knights), Bishops(bishops),
          Rooks(rooks), Queens(queens), Kings(kings),
          WhitePieces(whitePieces), BlackPieces(blackPieces){};

    ~Position();

    void Display() const;

    std::vector<Move> *GenerateLegalMoves(Magics &m) const;
};

#include "bitboard.h"
#include "constants.h"
#include "primitives.h"

#pragma once

class MailBox
{
  private:
    Piece list[64];

  public:
    MailBox();            // Constructs blank mailbox
    MailBox(Piece l[64]); // Constructs mailbox from a list of pieces
    MailBox(MailBox &m);  // Constructs mailbox with contents equal to m

    Piece Occupation(Square sq) const;  // Returns the piece on sq
    bool Occupied(Square sq) const;     // Returns whether a piece is on sq
    void SetSquare(Square sq, Piece p); // Sets the piece on sq to p
    BitBoard Pieces(Piece p) const;     // Debug method - can check sync with bitboards
};
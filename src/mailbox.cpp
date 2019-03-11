#include "mailbox.h"
#include "bitboard.h"
#include "constants.h"
#include "primitives.h"

MailBox::MailBox()
{
    for (int sq = 0; sq < NUM_SQUARES_BOARD; ++sq)
    {
        list[sq] = Piece::PIECE_NONE;
    }
}

MailBox::MailBox(Piece l[64])
{
    for (int sq = 0; sq < NUM_SQUARES_BOARD; ++sq)
    {
        list[sq] = l[sq];
    }
}

MailBox::MailBox(MailBox &m)
{
    for (int sq = 0; sq < NUM_SQUARES_BOARD; ++sq)
    {
        list[sq] = m.Occupation((Square)sq);
    }
}

Piece MailBox::Occupation(Square sq) const
{
    return list[(int)sq];
}

void MailBox::SetSquare(Square sq, Piece p)
{
    list[(int)sq] = p;
}

BitBoard MailBox::Pieces(Piece p) const
{
    BitBoard blank = BB_NoSquares;
    for (int sq = 0; sq < NUM_SQUARES_BOARD; ++sq)
    {
        if (list[sq] == p)
        {
            blank = blank ^ BBgenerate((Square)sq);
        }
    }
    return blank;
}

bool MailBox::Occupied(Square sq) const
{
    return !(list[(int)sq] == Piece::PIECE_NONE);
}
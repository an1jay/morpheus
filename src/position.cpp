#include "position.h"
#include "bitboard.h"
#include "constants.h"
#include "magics.h"

#include <iostream>
#include <vector>

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

// Updates BitBoards to match piece list
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

//Returns Bitboard for any piece
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

// Displays the board
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

// Returns piece at square
Piece Position::pieceAtSquare(Square sq)
{
    return PieceList.Occupation(sq);
}

std::vector<Move> *Position::GenerateLegalMoves(Magics &m) const
{
    std::vector<Move> legal_moves;
    Piece piece;
    BitBoard moves;
    Occupancy = BlackPieces ^ WhitePieces;
    for (int sq = 0; sq < NUM_SQUARES_BOARD; sq++)
    {
        piece = PieceList.Occupation((Square)sq);
        if (PieceColor(piece) == ColorToMove)
        {
            switch (piece)
            {
            case Piece::W_PAWN:
                /* code */
                break;

            case Piece::B_PAWN:
                /* code */
                break;

            case Piece::B_KNIGHT:
            case Piece::W_KNIGHT:
                moves = BlankKnightMoves[sq];
                break;

            case Piece::B_KING:
            case Piece::W_KING:
                moves = BlankKingMoves[sq];
                break;

            case Piece::B_BISHOP:
            case Piece::W_BISHOP:
                moves = m.AttackFor((Square)sq, Occupancy, PieceType::BISHOP);
                break;

            case Piece::B_ROOK:
            case Piece::W_ROOK:
                moves = m.AttackFor((Square)sq, Occupancy, PieceType::ROOK);
                break;

            case Piece::B_QUEEN:
            case Piece::W_QUEEN:
                moves = m.AttackFor((Square)sq, Occupancy, PieceType::BISHOP) ^
                        m.AttackFor((Square)sq, Occupancy, PieceType::ROOK);
                break;
            default:
                break;
            }

            while (moves)
            {
            }
        }
    }
}
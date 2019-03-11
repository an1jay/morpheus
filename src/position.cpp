#include "position.h"
#include "bitboard.h"
#include "constants.h"
#include "magics.h"
#include "move.h"
#include "primitives.h"

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
    SyncBBfromPieceList();

    ColorToMove = Color::WHITE;
}

// Updates BitBoards to match piece list
void Position::SyncBBfromPieceList()
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
            if (ColorFromPiece(p) == Color::WHITE)
                WhitePieces ^= BBgenerate((Square)sq);
            else
                BlackPieces ^= BBgenerate((Square)sq);
            break;
        case Piece::W_KNIGHT:
        case Piece::B_KNIGHT:
            Knights ^= BBgenerate((Square)sq);
            if (ColorFromPiece(p) == Color::WHITE)
                WhitePieces ^= BBgenerate((Square)sq);
            else
                BlackPieces ^= BBgenerate((Square)sq);
            break;
        case Piece::W_BISHOP:
        case Piece::B_BISHOP:
            Bishops ^= BBgenerate((Square)sq);
            if (ColorFromPiece(p) == Color::WHITE)
                WhitePieces ^= BBgenerate((Square)sq);
            else
                BlackPieces ^= BBgenerate((Square)sq);
            break;
        case Piece::W_ROOK:
        case Piece::B_ROOK:
            Rooks ^= BBgenerate((Square)sq);
            if (ColorFromPiece(p) == Color::WHITE)
                WhitePieces ^= BBgenerate((Square)sq);
            else
                BlackPieces ^= BBgenerate((Square)sq);
            break;
        case Piece::W_QUEEN:
        case Piece::B_QUEEN:
            Queens ^= BBgenerate((Square)sq);
            if (ColorFromPiece(p) == Color::WHITE)
                WhitePieces ^= BBgenerate((Square)sq);
            else
                BlackPieces ^= BBgenerate((Square)sq);
            break;
        case Piece::W_KING:
        case Piece::B_KING:
            Kings ^= BBgenerate((Square)sq);
            if (ColorFromPiece(p) == Color::WHITE)
                WhitePieces ^= BBgenerate((Square)sq);
            else
                BlackPieces ^= BBgenerate((Square)sq);
            break;
        default:
            break;
        }
    }
    Occupancy = WhitePieces ^ BlackPieces;
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
    Piece p;
    BitBoard moves;

    Move finalMove;

    Move targetSq;
    Move color;
    Move piece;
    Move capture;
    Move promotion;
    Move castle;
    Move enpassant;

    for (int sq = 0; sq < NUM_SQUARES_BOARD; sq++)
    {
        p = PieceList.Occupation((Square)sq);
        if (ColorFromPiece(p) == ColorToMove)
        {
            switch (p)
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

            moves = moves & ~((ColorToMove == Color::BLACK) ? BlackPieces : WhitePieces);

            while (moves)
            {
                finalMove = sq;
                targetSq = (Move)BBfindMSB(moves);
                color = (Move)ColorToMove;
                piece = (Move)p;
                if (PieceList.Occupied((Square)targetSq))
                    capture = 1ULL;
                castle = 0ULL;
                enpassant = 0ULL; // TODO make working

                finalMove ^= targetSq << TARGET_SQ_SHIFT;
                finalMove ^= color << COLOR_SHIFT;
                finalMove ^= piece << PIECE_SHIFT;
                finalMove ^= castle << CASTLE_SHIFT;
                finalMove ^= enpassant << ENPASSANT_SHIFT;

                if ((p == Piece::W_PAWN || p == Piece::B_PAWN) && (((BBgenerate((Square)targetSq) & BB_Rank8) != 0) || ((BBgenerate((Square)targetSq) & BB_Rank1) != 0)))
                {
                    legal_moves.emplace_back(finalMove ^ ((Move)PieceFromTypeColor(PieceType::KNIGHT, ColorToMove) << PROMOTION_SHIFT));
                    legal_moves.emplace_back(finalMove ^ ((Move)PieceFromTypeColor(PieceType::BISHOP, ColorToMove) << PROMOTION_SHIFT));
                    legal_moves.emplace_back(finalMove ^ ((Move)PieceFromTypeColor(PieceType::ROOK, ColorToMove) << PROMOTION_SHIFT));
                    legal_moves.emplace_back(finalMove ^ ((Move)PieceFromTypeColor(PieceType::QUEEN, ColorToMove) << PROMOTION_SHIFT));
                }
                else
                {
                    promotion = (Move)Piece::PIECE_NONE;
                    finalMove ^= promotion << PROMOTION_SHIFT;
                    legal_moves.emplace_back(finalMove);
                }
            }
        }
    }
}

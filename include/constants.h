#include "primitives.h"

#pragma once

constexpr int NUM_SQUARES_BOARD = 64;
constexpr int NUM_FILES = 8;
constexpr int NUM_RANKS = 8;
constexpr int NUM_SQUARES_LINE = 8;
constexpr int NUM_PIECES = 12;

constexpr Piece AllPieces[] = {Piece::W_PAWN, Piece::W_KNIGHT, Piece::W_BISHOP, Piece::W_ROOK, Piece::W_QUEEN, Piece::W_KING,
                               Piece::B_PAWN, Piece::B_KNIGHT, Piece::B_BISHOP, Piece::B_ROOK, Piece::B_QUEEN, Piece::B_KING};

constexpr char PieceChars[17] = {' ', 'P', 'N', 'B', 'R', 'Q', 'K', ' ', ' ',
                                 'p', 'n', 'b', 'r', 'q', 'k', ' ', ' '};

constexpr int ORIGIN_SQ_WIDTH = 6;
constexpr int TARGET_SQ_WIDTH = 6;
constexpr int COLOR_WIDTH = 2;
constexpr int PIECE_WIDTH = 4;
constexpr int CAPTURE_WIDTH = 1;
constexpr int PROMOTION_WIDTH = 4;
constexpr int CASTLE_WIDTH = 2;
constexpr int ENPASSANT_WIDTH = 6;

constexpr int ORIGIN_SQ_SHIFT = 0;
constexpr int TARGET_SQ_SHIFT = ORIGIN_SQ_SHIFT + ORIGIN_SQ_WIDTH;
constexpr int COLOR_SHIFT = TARGET_SQ_SHIFT + TARGET_SQ_WIDTH;
constexpr int PIECE_SHIFT = COLOR_SHIFT + COLOR_WIDTH;
constexpr int CAPTURE_SHIFT = PIECE_SHIFT + PIECE_WIDTH;
constexpr int PROMOTION_SHIFT = CAPTURE_SHIFT + CAPTURE_WIDTH;
constexpr int CASTLE_SHIFT = PROMOTION_SHIFT + PROMOTION_WIDTH;
constexpr int ENPASSANT_SHIFT = CASTLE_SHIFT + CASTLE_WIDTH;

constexpr Move ORIGIN_SQ_MASK = ((1ULL << ORIGIN_SQ_WIDTH) - 1) << ORIGIN_SQ_SHIFT;
constexpr Move TARGET_SQ_MASK = ((1ULL << TARGET_SQ_WIDTH) - 1) << TARGET_SQ_SHIFT;
constexpr Move COLOR_MASK = ((1ULL << COLOR_WIDTH) - 1) << COLOR_SHIFT;
constexpr Move PIECE_MASK = ((1ULL << PIECE_WIDTH) - 1) << PIECE_SHIFT;
constexpr Move CAPTURE_MASK = ((1ULL << CAPTURE_WIDTH) - 1) << CAPTURE_SHIFT;
constexpr Move PROMOTION_MASK = ((1ULL << PROMOTION_WIDTH) - 1) << PROMOTION_SHIFT;
constexpr Move CASTLE_MASK = ((1ULL << CASTLE_WIDTH) - 1) << CASTLE_SHIFT;
constexpr Move ENPASSANT_MASK = ((1ULL << ENPASSANT_WIDTH) - 1) << ENPASSANT_SHIFT;


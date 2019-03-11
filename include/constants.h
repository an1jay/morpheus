#pragma once

#include "move.h"
#include "primitives.h"

constexpr int NUM_SQUARES_BOARD = 64;
constexpr int NUM_FILES = 8;
constexpr int NUM_RANKS = 8;
constexpr int NUM_SQUARES_LINE = 8;
constexpr int NUM_PIECES = 12;

constexpr Piece AllPieces[] = {Piece::W_PAWN, Piece::W_KNIGHT, Piece::W_BISHOP, Piece::W_ROOK, Piece::W_QUEEN, Piece::W_KING,
                               Piece::B_PAWN, Piece::B_KNIGHT, Piece::B_BISHOP, Piece::B_ROOK, Piece::B_QUEEN, Piece::B_KING};

constexpr char PieceChars[17] = {' ', 'P', 'N', 'B', 'R', 'Q', 'K', ' ', ' ',
                                 'p', 'n', 'b', 'r', 'q', 'k', ' ', ' '};

constexpr char ColorChars[3] = {' ', 'W', 'B'};

constexpr char RankChars[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};

constexpr char FileChars[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};

constexpr char CaptureChars[2] = {'-', 'x'};
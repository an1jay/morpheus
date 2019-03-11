#include "move.h"
#include "constants.h"
#include "primitives.h"

char *EnglishFromMove(Move m)
{
    char *c = new char[12];
    int i = 0;
    c[i++] = ColorChars[((m & COLOR_MASK) >> COLOR_SHIFT)];
    c[i++] = '-';
    c[i++] = PieceChars[((m & PIECE_MASK) >> PIECE_SHIFT)];
    c[i++] = '-';
    c[i++] = FileChars[fileFromSq((Square)((m & ORIGIN_SQ_MASK) >> ORIGIN_SQ_SHIFT))];
    c[i++] = RankChars[rankFromSq((Square)((m & ORIGIN_SQ_MASK) >> ORIGIN_SQ_SHIFT))];
    c[i++] = CaptureChars[((m & CAPTURE_MASK) >> CAPTURE_SHIFT)];
    c[i++] = FileChars[fileFromSq((Square)((m & TARGET_SQ_MASK) >> TARGET_SQ_SHIFT))];
    c[i++] = RankChars[rankFromSq((Square)((m & TARGET_SQ_MASK) >> TARGET_SQ_SHIFT))];
    c[i++] = '=';
    c[i++] = PieceChars[((m & PROMOTION_MASK) >> PROMOTION_SHIFT)];
    c[i++] = '\0';
    return c;
}

// from 0 to 7
int rankFromSq(Square sq)
{
    return (int)sq / NUM_FILES;
}

// from 0 to 7
int fileFromSq(Square sq)
{
    return (int)sq % NUM_RANKS;
}
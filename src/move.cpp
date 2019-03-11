#include "move.h"
#include "constants.h"
#include "primitives.h"

char *EnglishFromMove(Move m)
{
    char c[10];
    c[0] = ColorChars[((m & COLOR_MASK) >> COLOR_SHIFT)];
    c[1] = PieceChars[((m & PIECE_MASK) >> PIECE_SHIFT)];
    c[2] = FileChars[fileFromSq((Square)((m & ORIGIN_SQ_MASK) >> ORIGIN_SQ_SHIFT))];
    c[3] = FileChars[rankFromSq((Square)((m & ORIGIN_SQ_MASK) >> ORIGIN_SQ_SHIFT))];
    c[4] = CaptureChars[((m & CAPTURE_MASK) >> CAPTURE_SHIFT)];
    c[5] = FileChars[fileFromSq((Square)((m & TARGET_SQ_MASK) >> TARGET_SQ_SHIFT))];
    c[6] = FileChars[rankFromSq((Square)((m & TARGET_SQ_MASK) >> TARGET_SQ_SHIFT))];
    C[7] = '=';
    c[8] = PieceChars[((m & PROMOTION_MASK) >> PROMOTION_SHIFT)];
    C[9] = '\0';
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
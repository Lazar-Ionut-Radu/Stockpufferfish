#ifndef _MOVE_H
#define _MOVE_H

#include "move.h"
#include "position.h"
#include "types.h"

// AN is short to algebraic notation.
// NOTE: pos is the position after the move was made.
char* move_to_AN(Position* pos, Move move);

// Plays the move on the board and updates the position accordingly.
void make_move(Position* pos, Move move);

// Returns the position to the state it was before the move was played.
void undo_move(Position* pos, Move move, enum Piece captured);

#endif // _MOVE_H

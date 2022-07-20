// Stockpufferfish (c) 2022 by Lazar Ionut-Radu
// This code is licensed under the terms of the GNU General 
// Public License (see licence.txt for details)

#ifndef _MOVE_H
#define _MOVE_H

#include "move.h"
#include "position.h"
#include "types.h"

// Returns the Algebraic Notation of the given move.
// NOTE: - pos is the position before the move was made.
//       - It is assumed that the move is legal.
void move_to_AN(char **AN, Position* pos, Move move);

// Plays the move on the board and updates the position accordingly.
// NOTE: It is assumed that the move is legal.
void make_move(Position* pos, Move move);

// Returns the position to the state it was before the move was played.
void undo_move(Position* pos, Move move, enum Piece captured);

#endif // _MOVE_H

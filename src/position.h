// Stockpufferfish (c) 2022 by Lazar Ionut-Radu
// This code is licensed under the terms of the GNU General 
// Public License (see licence.txt for details)

#ifndef _POSITION_H
#define _POSITION_H

#include "types.h"

// Sets up the initial position of a game of chess.
void position_init(Position* pos);

// Adds a piece on a specified square.
void add_piece(Position* pos, int square, int piece);

// Sets up a position given the FEN string.
Position FEN_to_position(char *FEN);

// Outputs the FEN string of a given position.
char* position_to_FEN(Position* pos);

// Returns the piece on a particular square.
enum Piece get_piece(Position* pos, int square);

// Prints a position in stdout.
void printf_position(Position* pos);

// Prints all the information about a position in stdout. 
void printf_position_debug(Position* pos);

#endif // _POSITION_H

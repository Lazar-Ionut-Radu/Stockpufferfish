#ifndef _POSITION_H
#define _POSITION_H

#include "types.h"

// Sets up the initial position of a game of chess.
void position_init(Position* pos);

// Sets up a position given the FEN string.
Position FEN_to_position(char *FEN);

// Outputs the FEN string of a given position.
char* position_to_FEN(Position* pos);

// Prints a position in stdout.
void printf_position(Position* pos);

#endif // _POSITION_H

// Stockpufferfish (c) 2022 by Lazar Ionut-Radu
// This code is licensed under the terms of the GNU General 
// Public License (see licence.txt for details)

#include "position.h"
#include "move.h"
#include "types.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    Position pos;
    pos = FEN_to_position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
    // printf_position_debug(&pos);

    Move move = get_move(E6, E7, 0, NORMAL);
    
    char *AN = malloc(sizeof(char) * 100);
    move_to_AN(&AN, &pos, move);
    printf("\n%s\n", AN);
    free(AN);

    return 0;
}
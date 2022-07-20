#include <stdio.h>
#include "types.h"
#include "position.h"
#include "move.h"

int main(void)
{
    Position pos = FEN_to_position("r3k2r/pppppppp/8/8/3p4/8/PPPPPPPP/R3K2R w KQkq h8 0 0");
    
    make_move(&pos, get_move(C4, C2, 0, NORMAL));

    printf_position_debug(&pos);

    make_move(&pos, get_move(C3, D4, 0, EN_PASSANT));

    printf_position_debug(&pos);

    return 0;
}
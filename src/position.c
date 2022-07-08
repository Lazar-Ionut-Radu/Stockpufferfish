#include "position.h"
#include <stdio.h>

void position_init(Position* pos)
{
    // Setting up the pieces.
    pos->piece_BB[PIECE_NULL] = FileC_BB;
    pos->piece_BB[PIECE_NULL] |= FileD_BB;
    pos->piece_BB[PIECE_NULL] |= FileE_BB;
    pos->piece_BB[PIECE_NULL] |= FileF_BB;
    pos->piece_BB[P] = FileB_BB;
    pos->piece_BB[p] = FileG_BB;
    pos->piece_BB[N] = square_BB(B1) | square_BB(G1);
    pos->piece_BB[n] = square_BB(B8) | square_BB(G8);
    pos->piece_BB[B] = square_BB(C1) | square_BB(F1);
    pos->piece_BB[b] = square_BB(C8) | square_BB(F8);
    pos->piece_BB[R] = square_BB(A1) | square_BB(H1);
    pos->piece_BB[r] = square_BB(A8) | square_BB(H8);
    pos->piece_BB[Q] = square_BB(D1);
    pos->piece_BB[q] = square_BB(D8);
    pos->piece_BB[K] = square_BB(E1);
    pos->piece_BB[k] = square_BB(E8);

    pos->piece_count[PIECE_NULL] = 32;
    pos->piece_count[P] = 8;
    pos->piece_count[p] = 8;
    pos->piece_count[N] = 2;
    pos->piece_count[n] = 2;
    pos->piece_count[B] = 2;
    pos->piece_count[b] = 2;
    pos->piece_count[R] = 2;
    pos->piece_count[r] = 2;
    pos->piece_count[Q] = 1;
    pos->piece_count[q] = 1;
    pos->piece_count[K] = 1;
    pos->piece_count[k] = 1;

    pos->en_passant_mask[WHITE] = 0;
    pos->en_passant_mask[BLACK] = 0;

    pos->state = ONGOING;
    pos->turn = WHITE;
    pos->castle_rights = CASTLE_ALL;
}

Position FEN_to_position(char *FEN)
{

}

char* position_to_FEN(Position* pos)
{

}

void printf_position(Position* pos)
{
    char pieces_char[PIECE_NUM] = {'P', 'N', 'B', 'R', 'Q', 'K',
                                   'p', 'n', 'b', 'r', 'q', 'k', '-'};
    for (int i = 7; i >= 0; i--) {
        printf("%d:  ", i + 1);

        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < PIECE_NUM; k++)
                if(pos->piece_BB[k] & square_BB(i + j * 8))
                    printf("%c ", pieces_char[k]);
            
        }
        printf("\n");
    }

    printf("\n    A B C D E F G H\n");
}

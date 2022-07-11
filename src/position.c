#include "position.h"
#include <stdio.h>

void position_init(Position* pos)
{
    FEN_to_position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");

    pos->en_passant_mask[WHITE] = 0;
    pos->en_passant_mask[BLACK] = 0;

    pos->state = ONGOING;
}

void add_piece(Position* pos, int square, int piece)
{
    if (!pos)
        return;

    if (!on_board_square(square))
        return;

    if (!is_valid_piece(piece))
        return;

    int was_changed = 0;
    Bitboard changed_square_BB = square_BB(square);
    for (int i = 0; i < PIECE_NUM; i++)
        if (pos->piece_BB[i] & changed_square_BB) {

            pos->piece_BB[i] -= changed_square_BB;
            pos->piece_count[i]--;
 
            pos->piece_BB[piece] += changed_square_BB;
            pos->piece_count[piece]++;

            was_changed = 1;
            break;
        }
    
    if (!was_changed) {
        pos->piece_BB[piece] += changed_square_BB;
        pos->piece_count[piece]++;
    }

}

Position FEN_to_position(char *FEN)
{
    // TODO: add en_passant and half/full move clock
    
    // Initializing.
    Position pos;
    pos.state = ONGOING;
    pos.castle_rights = 0;
    pos.en_passant_mask[WHITE] = 0;    
    pos.en_passant_mask[BLACK] = 0;
    for (int i = 0; i < PIECE_NUM; i++) {
        pos.piece_BB[i] = 0;
        pos.piece_count[i] = 0;
    }
    
    int index = 0;
    int square = A8;
    char pieces_chars[12] = {'P', 'N', 'B', 'R', 'Q', 'K',
                             'p', 'n', 'b', 'r', 'q', 'k'};

    while (FEN[index]) {
        if (FEN[index] == ' ') {
            index++;
            continue;
        }

        if (FEN[index] == '/') {
            index++;
            square -= 65;
            continue;
        }
        
        // Handling pieces.
        if (1) {
            int has_changed = 0;
            for (int i = 0; i < 12; i++) {
                if (FEN[index] == pieces_chars[i]) {
                    add_piece(&pos, square, i);

                    square += 8;
                    index++;
                    has_changed = 1;
                    break;
                }
            }
            if (has_changed)
                continue;

            has_changed = 0;
            if (FEN[index] >= '1' && FEN[index] <= '8') {
                int num = FEN[index] - '1';
                for (int i = 0; i <= num; i++) {
                    add_piece(&pos, square, PIECE_NULL);
                    square += 8;
                    has_changed = 1;
                }
                index++;
            }
            if (has_changed)
                continue;
            }

        // Handling turn.
        if (FEN[index] == 'w') {
            pos.turn = WHITE;
            index++;
            continue;
        }

        if (FEN[index] == 'b') {
            pos.turn = BLACK;
            index++;
            continue;
        }

        // Handling castling rights 
        if (FEN[index] == 'K') {
            pos.castle_rights += CASTLE_BLACK_OO;
            index++; 
            continue;
        }
        else if (FEN[index] == 'Q') {
            pos.castle_rights += CASTLE_BLACK_OOO;
            index++;
            continue;
        }
        else if (FEN[index] == 'k') { 
            pos.castle_rights += CASTLE_WHITE_OO;
            index++;
            continue;
        }
        else if (FEN[index] == 'q') { 
            pos.castle_rights += CASTLE_WHITE_OOO;
            index++;
            continue;
        }
    }

    return pos;
}

char* position_to_FEN(Position* pos)
{

}

void printf_position(Position* pos)
{
    char pieces_char[PIECE_NUM] = {'P', 'N', 'B', 'R', 'Q', 'K',
                                   'p', 'n', 'b', 'r', 'q', 'k', '-'};
    for (int rank = 7; rank >= 0; rank--) {
        printf("%d:  ", rank + 1);

        for (int file = 0; file < 8; file++) {
            for (int k = 0; k < PIECE_NUM; k++)
                if(pos->piece_BB[k] & square_BB((file*8 + rank)))
                    printf("%c ", pieces_char[k]);
            
        }
        printf("\n");
    }

    printf("\n    A B C D E F G H\n");
}

void printf_position_debug(Position* pos)
{
    char pieces_char[PIECE_NUM] = {'P', 'N', 'B', 'R', 'Q', 'K',
                                   'p', 'n', 'b', 'r', 'q', 'k', '-'};
    printf_position(pos);

    printf("Number of pieces: ");
    for (int i = 0; i < PIECE_NUM; i++)
        printf("%c:%d ", pieces_char[i], pos->piece_count[i]);

    printf("\nCastling rights: ");
    if (pos->castle_rights & CASTLE_WHITE_OO)
        printf("K");
    if (pos->castle_rights & CASTLE_WHITE_OOO)
        printf("Q");
    if (pos->castle_rights & CASTLE_BLACK_OO)
        printf("k");
    if (pos->castle_rights & CASTLE_BLACK_OOO)
        printf("q");

    printf("\nTurn: ");
    if (pos->turn == WHITE)
        printf("White");
    else 
        printf("Black");
    printf("\n");

}

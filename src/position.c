// Stockpufferfish (c) 2022 by Lazar Ionut-Radu
// This code is licensed under the terms of the GNU General 
// Public License (see licence.txt for details)

#include "position.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void position_init(Position* pos)
{
    *pos = FEN_to_position("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");

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
    pos.halfmove_clock = 0;
    pos.fullmove_clock = 0;
    
    int index = 0;
    int square = A8;
    char pieces_chars[12] = {'P', 'N', 'B', 'R', 'Q', 'K',
                             'p', 'n', 'b', 'r', 'q', 'k'};

    // Looping through the string.
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
        if (square != 64) {
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

        // En passant.
        if (FEN[index] == '-') {
            pos.en_passant_mask[WHITE] = NULL_BB;
            pos.en_passant_mask[BLACK] = NULL_BB;
            
            index++;
            continue;
        }
        else if (FEN[index + 1] >= '1' && FEN[index + 1] <= '8' && 
                 FEN[index] >= 'a' && FEN[index] <= 'h')  {
            int square_en_passant = (FEN[index] - 'a') * 8 + (FEN[index + 1] - '1');
            pos.en_passant_mask[pos.turn] = square_BB(square_en_passant);
            pos.en_passant_mask[OPPOSITE_COLOR(pos.turn)] = NULL_BB;
            
            index += 2;
            continue;
        }
        
        // Halfmove and fullmove clock.
        while (FEN[index] != ' ') {
            pos.halfmove_clock = pos.halfmove_clock * 10 + (FEN[index] - '0');
            index++;
        }
        index++;
        while (FEN[index]) {
            pos.fullmove_clock = pos.fullmove_clock * 10 + (FEN[index] - '0');
            index++;
        }
    }

    return pos;
}

char* position_to_FEN(Position* pos)
{
}

enum Piece get_piece(Position* pos, int square)
{
    for (int i = 0; i < PIECE_NUM; i++) {
        if (pos->piece_BB[i] & square_BB(square))
            return i;
    }
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
    
    if (square(pos->en_passant_mask[OPPOSITE_COLOR(pos->turn)]))
        printf("\nEn passant square: %c%d\n", square(pos->en_passant_mask[OPPOSITE_COLOR(pos->turn)]) / 8 + 'a',
                                              square(pos->en_passant_mask[OPPOSITE_COLOR(pos->turn)]) % 8 + 1);
    else
        printf("\nEn passant square: -\n");

    printf("Halfmove / Fullmove clock: %d %d\n", pos->halfmove_clock, pos->fullmove_clock);
}

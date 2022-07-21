// Stockpufferfish (c) 2022 by Lazar Ionut-Radu
// This code is licensed under the terms of the GNU General 
// Public License (see licence.txt for details)

#include "move.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

// TODO : 1) add ++ / # to show check & checkmate
//        2) add a check for ambiguity. Moves like Rdf8 as opposed 
//                                               to Rf8
//        3) whyyy doesn't it work...
void move_to_AN(char **AN, Position* pos, Move move)
{
    enum Square dest = get_dest_square(move);
    enum Square origin = get_origin_square(move);

    enum Piece piece; // The moved piece.
    piece = get_piece(pos, origin);

    char pieces_chars[12] = {'P', 'N', 'B', 'R', 'Q', 'K',
                             'P', 'N', 'B', 'R', 'Q', 'K'};
    // Castling:
    if (is_castling(move)) {
        if (dest == G1 || dest == G8)
            strcpy(*AN, "O-O\0");
        else 
            strcpy(*AN ,"O-O-O\0");

        return;
    }

    int index = 0;

    // Pawn moves:
    if (piece == P || piece == p)
    {
        // Pawn capture:
        if (!(abs(dest - origin) <= 2)) {
            (*AN)[index++] = origin / 8 + 'a';
            (*AN)[index++] = 'x';
        }

        (*AN)[index++] = dest / 8 + 'a';
        (*AN)[index++] = dest % 8 + '1';
        
        // Promotions:
        if (is_promotion(move)) {
            (*AN)[index++] = '=';
            
            if (get_promoted_piece(move) == PROM_KNIGHT)
                (*AN)[index++] = pieces_chars[N];
            else if (get_promoted_piece(move) == PROM_BISHOP)
                (*AN)[index++] = pieces_chars[B];
            else if (get_promoted_piece(move) == PROM_ROOK)
                (*AN)[index++] = pieces_chars[R];
            else if (get_promoted_piece(move) == PROM_QUEEN)
                (*AN)[index++] = pieces_chars[Q];
        }

        // En passant:
        if (is_en_passant(move)) {
            strcpy((*AN) + index, " e.p.");
            index += 5;
        }
    }
    // Non-pawn moves
    else {
        (*AN)[index++] = pieces_chars[piece];
        
        // Capture
        if (!(pos->piece_BB[PIECE_NULL] & square_BB(dest))) {
            (*AN)[index++] = 'x';
        }

        (*AN)[index++] = dest / 8 + 'a';
        (*AN)[index++] = dest % 8 + '1';   
    }

    (*AN)[index++] = '\0';
}

void make_move(Position* pos, Move move)
{
    // Updates the halfmove clock.
    if (get_piece(pos, get_dest_square(move)) != PIECE_NULL) 
        pos->halfmove_clock = 0;
    else if (get_piece(pos, get_origin_square(move)) == P ||
             get_piece(pos, get_origin_square(move)) == p)
        pos->halfmove_clock = 0;
    else
        pos->halfmove_clock++;

    // Plays the move on the board.
    enum Square dest = get_dest_square(move);
    enum Square origin = get_origin_square(move);
    enum Piece piece; // The moved piece.
    
    // For pawn promotion.
    if (is_promotion(move))
        piece = (get_promoted_piece(move) >> 12) + 1 + pos->turn * 6;
    else
        piece = get_piece(pos, origin);
    
    // Moves the piece.
    add_piece(pos, dest, piece);
    add_piece(pos, origin, PIECE_NULL);

    // Removes the captured pawn in en_passant.
    if (is_en_passant(move)) {
        add_piece(pos, square(pos->en_passant_mask[OPPOSITE_COLOR(pos->turn)]), PIECE_NULL);
    }

    // Moves the rook in castling moves.
    if (is_castling(move)) {
        if (dest == G1) {
            add_piece(pos, H1, PIECE_NULL);
            add_piece(pos, F1, R);
            if (pos->castle_rights & CASTLE_WHITE_OO)
                pos->castle_rights -= CASTLE_WHITE_OO; 
        }
        else if (dest == C1) {
            add_piece(pos, A1, PIECE_NULL);
            add_piece(pos, D1, R);
            if (pos->castle_rights & CASTLE_WHITE_OOO)
                pos->castle_rights -= CASTLE_WHITE_OOO; 
        }
        else if (dest == G8) {
            add_piece(pos, G1, PIECE_NULL);
            add_piece(pos, G1, r);
            if (pos->castle_rights & CASTLE_BLACK_OO)
                pos->castle_rights -= CASTLE_BLACK_OO; 
        }
        else if (dest == C8) {
            add_piece(pos, A8, PIECE_NULL);
            add_piece(pos, D8, r);
            if (pos->castle_rights & CASTLE_BLACK_OOO)
                pos->castle_rights -= CASTLE_BLACK_OOO; 
        }
    }

    // Updates castling rights after the move.
    if (pos->castle_rights & CASTLE_WHITE_OO) {
        if (origin == H1 || origin == E1) 
            pos->castle_rights -= CASTLE_WHITE_OO;
    }
    if (pos->castle_rights & CASTLE_WHITE_OOO) {
        if (origin == A1 || origin == E1) 
            pos->castle_rights -= CASTLE_WHITE_OOO;
    }
    if (pos->castle_rights & CASTLE_BLACK_OO) {
        if (origin == H8 || origin == E8) 
            pos->castle_rights -= CASTLE_BLACK_OO;
    }
    if (pos->castle_rights & CASTLE_BLACK_OOO) {
        if (origin == A8 || origin == E8) 
            pos->castle_rights -= CASTLE_BLACK_OOO;
    }

    // Updates the en passant mask bitmap.
    if (piece == P && dest - origin == 2) {
        pos->en_passant_mask[WHITE] = square_BB(dest);
    }
    else if (piece == p && origin - dest == 2)
        pos->en_passant_mask[BLACK] = square_BB(dest);
    else 
        pos->en_passant_mask[WHITE] = pos->en_passant_mask[BLACK] = NULL_BB;

    // Updates fullmove clock.
    if (pos->turn == BLACK)
        pos->fullmove_clock++;
    
    // Updates the turn.
    pos->turn = OPPOSITE_COLOR(pos->turn);
}

void undo_move(Position* pos, Move move, enum Piece captured)
{

}



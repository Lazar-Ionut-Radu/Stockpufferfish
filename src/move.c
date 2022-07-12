#include "move.h"

char* move_to_AN(Position* pos, Move move)
{
    
}

// TODO: update pos->en_passant_mask[]
//       handle castling
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
    enum Piece piece;
    if (is_promotion(move))
        piece = (get_promoted_piece(move) >> 12) + 1 + pos->turn * 6;
    else
        piece = get_piece(pos, origin);
    
    add_piece(pos, dest, piece);
    add_piece(pos, origin, PIECE_NULL);
    if (is_en_passant(move) && !is_castling(move)) 
        add_piece(pos, square(pos->en_passant_mask[pos->turn]), PIECE_NULL);

    if (is_castling(move)) {
        // TODO
    }

    // Updates fullmove clock.
    if (pos->turn == BLACK)
        pos->fullmove_clock++;
    
    // Updates the turn.
    pos->turn = OPPOSITE_COLOR(pos->turn);
}

void undo_move(Position* pos, Move move, enum Piece captured)
{

}



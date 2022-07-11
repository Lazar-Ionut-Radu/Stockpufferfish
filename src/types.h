#ifndef _TYPES_H
#define _TYPES_H

#include <stdlib.h>
#include "bitboard.h"

// The squares on the table can be represented on 6 bits as the numbers 0-63
enum Square {A1, A2, A3, A4, A5, A6, A7, A8,
             B1, B2, B3, B4, B5, B6, B7, B8,
             C1, C2, C3, C4, C5, C6, C7, C8,
             D1, D2, D3, D4, D5, D6, D7, D8,
             E1, E2, E3, E4, E5, E6, E7, E8,
             F1, F2, F3, F4, F5, F6, F7, F8,
             G1, G2, G3, G4, G5, G6, G7, G8,
             H1, H2, H3, H4, H5, H6, H7, H8};

#define SQUARE_NUM 64

// The bit board equivalent of a square
#define square_BB(SQ) ((int64_t)(1ULL << SQ)) 

// Returns 1 if the piece has a valid value, 0 otherwise
#define is_valid_square(SQ) (0 <= SQ && 64 >= SQ)
#define on_board_square(SQ) (0 <= SQ && 63 >= SQ)

// The adjacent squares to SQ
#define squareN(SQ)  (SQ - 8)
#define squareS(SQ)  (SQ + 8)
#define squareE(SQ)  (SQ + 1)
#define squareW(SQ)  (SQ - 1)
#define squareNE(SQ) (SQ - 7)
#define squareNW(SQ) (SQ - 9)
#define squareSE(SQ) (SQ + 9)
#define squareSW(SQ) (SQ + 7)

// A move can be represented on 16 bits as such
//
// bits  0- 5: dest square (from 0 to 63)
// bits  6-11: origin square (from 0 to 63)
// bits 12-13: promotion piece type: 0 - knight
//                                   1 - bishop
//                                   2 - rook
//                                   3 - queen
// bits 14-15: move type flag: 0 - normal
//                             1 - promotion
//                             2 - en passant
//                             3 - castling
typedef int16_t Move;

// Move type flags
#define NORMAL      0
#define PROMOTION  (1 << 14)
#define EN_PASSANT (2 << 14)
#define CASTLING   (3 << 14)

// Promoted pieces
#define PROM_KNIGHT  0
#define PROM_BISHOP (1 << 12)
#define PROM_ROOK   (2 << 12)
#define PROM_QUEEN  (3 << 12)

// Returns the move given it's components
// @param DEST: Destination square
// @param ORIGIN: Origin square
// @param PIECE: Promoted piece
// @param FLAG: The move type 
#define get_move(DEST, ORIGIN, PROM, FLAG) ((Move)(DEST | (ORIGIN << 6) | PROM | FLAG))

// Piece type : Uppercase - White pieces
//              Lowercase - Black pieces
//              P/p       - Pawn
//              N/n       - Knight
//              B/b       - Bishop
//              R/r       - Rook
//              Q/q       - Queen
//              K/k       - King
enum Piece {P, N, B, R, Q, K,
            p, n, b, r, q, k,
            PIECE_NULL};

#define PIECE_NUM 13

// Returns the black/white version of the piece
#define piece_to_black(PIECE) (PIECE <= 5 ? (PIECE + 5) : PIECE)
#define piece_to_white(PIECE) (PIECE >  5 ? (PIECE - 5) : PIECE)

// Returns 1 if the piece has a valid value, 0 otherwise
#define is_valid_piece(PIECE) (0 <= PIECE && PIECE <= 12)

// The state of the game.
enum State {ONGOING, UNKNOWN, DRAW, WIN, LOSE};

// Castling rights can be represented on 4 bits:
//   bit 0: White's king side castle
//   bit 1: White's queen side castle
//   bit 2: Black's king side castle
//   bit 3: Black's queen side castle
typedef int16_t CastlingRights;

#define CASTLE_WHITE_OO     1
#define CASTLE_WHITE_OOO    2
#define CASTLE_BLACK_OO     4
#define CASTLE_BLACK_OOO    8
#define CASTLE_ALL          15
#define CASTLE_WHITE        3
#define CASTLE_BLACK        12
#define CASTLE_KING_SIDE    5
#define CASTLE_QUEEN_SIDE   10
#define CASTLE_NULL         0
 
enum Color {WHITE, BLACK};
#define COLOR_NUM 2

typedef int64_t Bitboard;

// Data type of a position.
typedef struct {
    // piece_BB[PIECE] = the bitboard of the piece "PIECE"
    // piece_BB[PIECE_NULL] = the empty squares on the board
    Bitboard piece_BB[PIECE_NUM];
    // Squares of the board where a pawn of the specified color can en_passant
    Bitboard en_passant_mask[COLOR_NUM];
    int piece_count[PIECE_NUM];
    CastlingRights castle_rights;
    enum Color turn;
    enum State state;
} Position;

#endif // _TYPES_H

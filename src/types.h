#ifndef _TYPES_H
#define _TYPES_H

#include <stdlib.h>

// The squares on the table can be represented on 6 bits as the numbers 0-63

enum Square {A1, A2, A3, A4, A5, A6, A7, A8,
             B1, B2, B3, B4, B5, B6, B7, B8,
             C1, C2, C3, C4, C5, C6, C7, C8,
             D1, D2, D3, D4, D5, D6, D7, D8,
             E1, E2, E3, E4, E5, E6, E7, E8,
             F1, F2, F3, F4, F5, F6, F7, F8,
             G1, G2, G3, G4, G5, G6, G7, G8,
             H1, H2, H3, H4, H5, H6, H7, H8};
 
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

#define NORMAL      0
#define PROMOTION  (1 << 14)
#define EN_PASSANT (2 << 14)
#define CASTLING   (3 << 14)

#define PROM_KNIGHT  0
#define PROM_BISHOP (1 << 12)
#define PROM_ROOK   (2 << 12)
#define PROM_QUEEN  (3 << 12)

// Returns the move given it's components
// @param DEST: Destination square
// @param ORIGIN: Origin square
// @param PIECE: Promoted piece
// @param FLAG: The move type 
#define get_move(DEST, ORIGIN, PROM, FLAG) (DEST | (ORIGIN << 6) | PROM | FLAG)

#endif // _TYPES_H

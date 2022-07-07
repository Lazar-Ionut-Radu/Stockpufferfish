#ifndef _BITBOARDS_H
#define _BITBOARDS_H

// A 64 bit number is used to encode some aspect of a board.
// Each bit represents a square on the board:
//      bit  0 - Square A1
//      bit  1 - Square A2
//      ...
//      bit  8 - Square B1
//      ...
//      bit 63 - Square H8

#define NoSquares_BB 
#define AllSquares_BB   0xFFFFFFFFFFFFFFFFULL
#define DarkSquares_BB  0xAA55AA55AA55AA55ULL
#define WhiteSquares_BB (~DarkSquares_BB)

#define FileA_BB 0x0101010101010101ULL;
#define FileB_BB 0x0202020202020202ULL;
#define FileC_BB 0x0404040404040404ULL;
#define FileD_BB 0x0808080808080808ULL;
#define FileE_BB 0x1010101010101010ULL;
#define FileF_BB 0x2020202020202020ULL;
#define FileG_BB 0x4040404040404040ULL;
#define FileH_BB 0x8080808080808080ULL;

#define Rank1_BB 0xFF;
#define Rank2_BB (Rank1_BB << (8 * 1))
#define Rank3_BB (Rank1_BB << (8 * 2))
#define Rank4_BB (Rank1_BB << (8 * 3))
#define Rank5_BB (Rank1_BB << (8 * 4))
#define Rank6_BB (Rank1_BB << (8 * 5))
#define Rank7_BB (Rank1_BB << (8 * 6))
#define Rank8_BB (Rank1_BB << (8 * 7))

#define QueenSide_BB (FileA_BB | FileB_BB | FileC_BB | FileD_BB)
#define KingSide_BB  (FileE_BB | FileF_BB | FileG_BB | FileH_BB)
#define Center_BB    ((FileD_BB | FileE_BB) & (Rank4_BB | Rank5_BB))

#endif // _BITBOARDS_H

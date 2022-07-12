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

#define Rank1_BB 0x0101010101010101ULL
#define Rank2_BB 0x0202020202020202ULL
#define Rank3_BB 0x0404040404040404ULL
#define Rank4_BB 0x0808080808080808ULL
#define Rank5_BB 0x1010101010101010ULL
#define Rank6_BB 0x2020202020202020ULL
#define Rank7_BB 0x4040404040404040ULL
#define Rank8_BB 0x8080808080808080ULL

#define FileA_BB 0xFFULL
#define FileB_BB (FileA_BB << (8 * 1))
#define FileC_BB (FileA_BB << (8 * 2))
#define FileD_BB (FileA_BB << (8 * 3))
#define FileE_BB (FileA_BB << (8 * 4))
#define FileF_BB (FileA_BB << (8 * 5))
#define FileG_BB (FileA_BB << (8 * 6))
#define FileH_BB (FileA_BB << (8 * 7))

#define QueenSide_BB (FileA_BB | FileB_BB | FileC_BB | FileD_BB)
#define KingSide_BB  (FileE_BB | FileF_BB | FileG_BB | FileH_BB)
#define Center_BB    ((FileD_BB | FileE_BB) & (Rank4_BB | Rank5_BB))
#define NULL_BB 0

// Least significant bit set to 1.
#define LSB(x) ((int64_t)x & (-x))

// Logarithm, to be more precise floor(log(x)).
// With the added caveat that here LOG(0) = 0
#define LOG_2(x) (((x) >= 2ULL) ? 1 : 0)
#define LOG_4(x) (((x) >= 1ULL<<2) ? (2 + LOG_2((x)>>2)) : LOG_2(x))
#define LOG_8(x) (((x) >= 1ULL<<4) ? (4 + LOG_4((x)>>4)) : LOG_4(x))
#define LOG_16(x) (((x) >= 1ULL<<8) ? (8 + LOG_8((x)>>8)) : LOG_8(x))
#define LOG_32(x) (((x) >= 1ULL<<16) ? (16 + LOG_16((x)>>16)) : LOG_16(x))
#define LOG(x)   (((x) >= 1ULL<<32) ? (32 + LOG_32((x)>>32)) : LOG_32(x))

// Most significant bit set to 1.
#define MSB(x) ((x == 0) ? 0 : (1ULL << LOG(x)))

#endif // _BITBOARDS_H

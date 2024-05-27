#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdint.h>
#include "tile.h"

typedef struct {
  Tile ** tiles;
  int16_t size;
} Board;

Board *construct_board(uint16_t x, uint16_t y, uint16_t size);

bool check_win(Board *board);

int toggle_board_tile(uint16_t x, uint16_t y, Board *board);

void print_board(Board *board);

void destroy_board(Board *board);

/**@}*/

#endif /* _Board_H_ */

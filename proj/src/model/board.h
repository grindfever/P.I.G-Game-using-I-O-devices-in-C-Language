#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdint.h>
#include "tile.h"

typedef struct Hint {
  int count;
  struct Hint* next;
} Hint;

typedef struct {
  Tile** tiles;
  int16_t size;
  uint8_t x; 
  uint8_t y;
  Hint** h_hints;
  Hint** v_hints;
} Board;

Board *construct_board(uint16_t x, uint16_t y, uint16_t size);

bool check_win(Board *board);

int toggle_board_tile(uint16_t x, uint16_t y, Board *board);

void print_h_hints(Board *board);

void print_board(Board *board);

void destroy_board(Board *board);

/**@}*/

#endif /* _Board_H_ */

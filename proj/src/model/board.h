#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdint.h>
#include <tile.h>

typedef struct {
  Tile ** tiles;
  int16_t size;
} Board;

Board *construct_board(int16_t x, int16_t y, int16_t size);

bool check_win(Board *board);

int toggle_board_tile(int16_t x, int16_t y, Board *board);

void destroy_board(Board *board);

/**@}*/

#endif /* _Board_H_ */

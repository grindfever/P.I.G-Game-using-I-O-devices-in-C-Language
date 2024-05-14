#ifndef _TILE_H_
#define _TILE_H_

#include <stdint.h>

typedef struct {
  int16_t x;      
  int16_t y;      
  int8_t on; //1 is on, 0 off
  int8_t solution; //1 or 0 
} Tile;

Tile *construct_tile(int16_t x, int16_t y, int8_t solution);

int toggle_tile(Tile *tile);

void destroy_tile(Tile *tile);

/**@}*/

#endif /* _Tile_H_ */

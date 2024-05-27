#ifndef _TILE_H_
#define _TILE_H_

#include <stdint.h>

typedef struct {
  int16_t x;      
  int16_t y;      
  int8_t on; //1 is on, 0 off
  int8_t solution; //1 or 0 
} Tile;

Tile construct_tile(uint16_t x, uint16_t y, uint8_t solution);

Tile toggle_tile(Tile tile);

int is_wrong(Tile tile);

/**@}*/

#endif /* _Tile_H_ */

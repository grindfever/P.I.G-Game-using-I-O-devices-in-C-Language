#include <lcom/lcf.h>

#include "tile.h"

Tile construct_tile(uint16_t x, uint16_t y, uint8_t solution) {
  Tile tile;

  tile.x = x;
  tile.y = y;
  tile.on = 0; //default 0 -> desligado
  tile.solution = solution;

  return tile;
}

Tile toggle_tile(Tile tile){
    if(tile.on){
        tile.on = 0;
    }
    else tile.on = 1;

    return tile;
}

int is_wrong(Tile tile){
    return !(tile.on == tile.solution);
}

void destroy_tile(Tile *tile) {
  if (tile)
    free(tile);
}

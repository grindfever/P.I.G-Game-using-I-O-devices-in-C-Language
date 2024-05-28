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

int toggle_tile(Tile* tile) {
    if (!tile) {
        return 1;
    }
    
    printf("Toggling tile at (%d, %d): current state = %d\n", tile->x, tile->y, tile->on);
    tile->on = !tile->on;
    printf("Toggled tile at (%d, %d): new state = %d\n", tile->x, tile->y, tile->on);

    return 0;
}

int is_wrong(Tile tile){
    return !(tile.on == tile.solution);
}

void destroy_tile(Tile *tile) {
  if (tile)
    free(tile);
}

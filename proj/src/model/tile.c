#include <lcom/lcf.h>

#include "tile.h"

extern uint32_t score;

Tile *construct_tile(int16_t x, int16_t y, uint8_t solution) {
  Tile *tile = (Tile *) malloc(sizeof(Tile));

  if (!tile) {
    printf("error creating tile -> NULL\n");
    return NULL;
  }

  tile->x = x;
  tile->y = y;
  tile->on = 0; //default 0 -> desligado
  tile->solution = solution;

  return tile;
}

int toggle_tile(Tile *tile){
    if(!tile){
        printf("error toggling tile -> NULL\n");
        return 1;
    }

    if(tile->on){
        tile->on = 0;
    }
    else tile->on = 1;

    return 0;
}

void destroy_tile(Tile *tile) {
  if (tile)
    free(tile);
}

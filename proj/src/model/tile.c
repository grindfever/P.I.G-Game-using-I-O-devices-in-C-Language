/**
 * @file tile.c
 * @brief Implementation of the Tile structure and its associated functions.
 */

#include <lcom/lcf.h>
#include "tile.h"

/**
 * @brief Constructs a tile with the given coordinates and solution state.
 * 
 * @param x The x-coordinate of the tile.
 * @param y The y-coordinate of the tile.
 * @param solution The solution state of the tile (1 or 0).
 * @return The constructed Tile.
 */
Tile construct_tile(uint16_t x, uint16_t y, uint8_t solution) {
  Tile tile;
  tile.x = x;
  tile.y = y;
  tile.on = 0; // default 0 -> off
  tile.solution = solution;
  return tile;
}

/**
 * @brief Toggles the state of a tile.
 * 
 * @param tile The tile to toggle.
 * @return 0 on success, 1 if the tile pointer is NULL.
 */
int toggle_tile(Tile* tile) {
    if (!tile) {
        return 1;
    }
    
    printf("Toggling tile at (%d, %d): current state = %d\n", tile->x, tile->y, tile->on);
    tile->on = !tile->on;
    printf("Toggled tile at (%d, %d): new state = %d\n", tile->x, tile->y, tile->on);

    return 0;
}

/**
 * @brief Checks if the tile is in the wrong state.
 * 
 * @param tile The tile to check.
 * @return 1 if the tile is in the wrong state, 0 otherwise.
 */
int is_wrong(Tile tile){
    return !(tile.on == tile.solution);
}

/**
 * @brief Destroys a tile and frees allocated memory.
 * 
 * @param tile The tile to destroy.
 */
void destroy_tile(Tile *tile) {
  if (tile)
    free(tile);
}

#ifndef _TILE_H_
#define _TILE_H_

#include <stdint.h>

/**
 * @brief Structure representing a tile.
 */
typedef struct {
  int16_t x;       /**< The x-coordinate of the tile. */
  int16_t y;       /**< The y-coordinate of the tile. */
  int8_t on;       /**< The current state of the tile (1 for on, 0 for off). */
  int8_t solution; /**< The solution state of the tile (1 or 0). */
} Tile;

/**
 * @brief Constructs a tile with the given coordinates and solution state.
 * 
 * @param x The x-coordinate of the tile.
 * @param y The y-coordinate of the tile.
 * @param solution The solution state of the tile (1 or 0).
 * @return The constructed Tile.
 */
Tile construct_tile(uint16_t x, uint16_t y, uint8_t solution);

/**
 * @brief Toggles the state of a tile.
 * 
 * @param tile The tile to toggle.
 * @return 0 on success, 1 if the tile pointer is NULL.
 */
int toggle_tile(Tile* tile);

/**
 * @brief Checks if the tile is in the wrong state.
 * 
 * @param tile The tile to check.
 * @return 1 if the tile is in the wrong state, 0 otherwise.
 */
int is_wrong(Tile tile);

/**
 * @brief Destroys a tile and frees allocated memory.
 * 
 * @param tile The tile to destroy.
 */
void destroy_tile(Tile *tile);

#endif /* _TILE_H_ */


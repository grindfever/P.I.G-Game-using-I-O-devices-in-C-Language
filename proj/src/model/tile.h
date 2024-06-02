#ifndef _TILE_H_
#define _TILE_H_

#include <stdint.h>

/**
 * @brief Represents a tile on the game board.
 */
typedef struct {
  int16_t x;         /**< The x-coordinate of the tile. */
  int16_t y;         /**< The y-coordinate of the tile. */
  int8_t on;         /**< Flag indicating if the tile is turned on (1) or off (0). */
  int8_t solution;   /**< The solution value of the tile (1 for on, 0 for off). */
} Tile;

/**
 * @brief Constructs a tile with the given coordinates and solution value.
 *
 * @param x The x-coordinate of the tile.
 * @param y The y-coordinate of the tile.
 * @param solution The solution value of the tile (1 for on, 0 for off).
 * @return The constructed tile.
 */
Tile construct_tile(uint16_t x, uint16_t y, uint8_t solution);

/**
 * @brief Toggles the state of the given tile (turns it on if off, off if on).
 *
 * @param tile Pointer to the tile to toggle.
 * @return 0 on success, 1 if the tile pointer is NULL.
 */
int toggle_tile(Tile* tile);

/**
 * @brief Checks if the tile is in the wrong state compared to its solution.
 *
 * @param tile The tile to check.
 * @return 1 if the tile is in the wrong state, 0 otherwise.
 */
int is_wrong(Tile tile);

/**
 * @brief Frees memory allocated for the given tile.
 *
 * @param tile Pointer to the tile to destroy.
 */
void destroy_tile(Tile *tile);

#endif /* _TILE_H_ */


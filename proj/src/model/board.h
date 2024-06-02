/**
 * @file board.h
 * @brief Header file for the Board module, containing definitions and function prototypes for board operations.
 */
#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdint.h>
#include "tile.h"


/**
 * @brief Structure representing a hint in the game.
 */
typedef struct Hint {
  int count;            /**< The count value for the hint. */
  struct Hint* next;    /**< Pointer to the next hint in the list. */
} Hint;

/**
 * @brief Structure representing the game board.
 */
typedef struct {
  Tile** tiles;         /**< 2D array of tiles representing the board. */
  int16_t size;         /**< The size of the board. */
  uint8_t x;            /**< The x-coordinate of the board. */
  uint8_t y;            /**< The y-coordinate of the board. */
  Hint** h_hints;       /**< Horizontal hints of the board. */
  Hint** v_hints;       /**< Vertical hints of the board. */
} Board;

/**
 * @brief Constructs a new Board.
 *
 * @param x The x-coordinate of the board.
 * @param y The y-coordinate of the board.
 * @param size The size of the board.
 * @return A pointer to the newly constructed Board.
 */
Board *construct_board(uint16_t x, uint16_t y, uint16_t size);

/**
 * @brief Checks if the player has won the game.
 *
 * @param board The game board.
 * @return True if the player has won, false otherwise.
 */
bool check_win(Board *board);

/**
 * @brief Toggles the state of a tile on the board.
 *
 * @param x The x-coordinate of the tile.
 * @param y The y-coordinate of the tile.
 * @param board The game board.
 * @return 1 if the tile coordinates are out of bounds, 0 otherwise.
 */
int toggle_board_tile(uint16_t x, uint16_t y, Board *board);

/**
 * @brief Prints the game board to the console.
 *
 * @param board The game board.
 */
void print_board(Board *board);

/**
 * @brief Prints the horizontal hints of the board to the console.
 *
 * @param board The game board.
 */
void print_h_hints(Board *board);

/**
 * @brief Destroys the game board and frees memory.
 *
 * @param board The game board to destroy.
 */
void destroy_board(Board *board);

#endif /* _Board_H_ */


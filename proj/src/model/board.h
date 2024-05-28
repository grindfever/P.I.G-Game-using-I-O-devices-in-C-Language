/**
 * @file board.h
 * @brief Header file for the Board module, containing definitions and function prototypes for board operations.
 */
#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdint.h>
#include "tile.h"

/**
 * @brief Structure representing a hint for the board.
 */
typedef struct Hint {
  int count;            /**< Number of tiles in the hint sequence. */
  struct Hint* next;    /**< Pointer to the next hint in the sequence. */
} Hint;

/**
 * @brief Structure representing the game board.
 */
typedef struct {
  Tile** tiles;         /**< 2D array of tiles. */
  int16_t size;         /**< Size of the board (width and height). */
  uint8_t x;            /**< X coordinate of the board's position. */
  uint8_t y;            /**< Y coordinate of the board's position. */
  Hint** h_hints;       /**< Horizontal hints for the board. */
  Hint** v_hints;       /**< Vertical hints for the board. */
} Board;

/**
 * @brief Constructs a new board.
 * 
 * @param x The X coordinate of the board's position.
 * @param y The Y coordinate of the board's position.
 * @param size The size of the board.
 * @return Pointer to the constructed board.
 */
Board *construct_board(uint16_t x, uint16_t y, uint16_t size);

/**
 * @brief Checks if the board is in a winning state.
 * 
 * @param board Pointer to the board.
 * @return True if the board is in a winning state, false otherwise.
 */
bool check_win(Board *board);

/**
 * @brief Toggles the state of a tile on the board.
 * 
 * @param x The X coordinate of the tile.
 * @param y The Y coordinate of the tile.
 * @param board Pointer to the board.
 * @return 0 upon success, non-zero otherwise.
 */
int toggle_board_tile(uint16_t x, uint16_t y, Board *board);

/**
 * @brief Prints the horizontal hints of the board.
 * 
 * @param board Pointer to the board.
 */
void print_h_hints(Board *board);

/**
 * @brief Prints the board to the console.
 * 
 * @param board Pointer to the board.
 */
void print_board(Board *board);

/**
 * @brief Destroys the board and frees allocated memory.
 * 
 * @param board Pointer to the board.
 */
void destroy_board(Board *board);

#endif /* _Board_H_ */

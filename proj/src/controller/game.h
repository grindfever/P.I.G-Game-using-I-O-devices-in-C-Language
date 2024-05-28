#ifndef GAME_H
#define GAME_H

#include "../model/board.h"

/**
 * @brief Handles mouse input for the game.
 * 
 * Reads mouse input and updates the game state accordingly.
 * 
 * @param b Pointer to the game board.
 */
void mouse_game_handler(Board* b);

#endif // GAME_H

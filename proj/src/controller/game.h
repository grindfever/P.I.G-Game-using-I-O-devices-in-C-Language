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

/**
 * @brief Draws the game mouse on the screen.
 * 
 * This function draws the game mouse at its current position on the screen
 * using the specified mouse sprite. It updates the graphics content after
 * drawing the mouse.
 * 
 * @return Returns 0 on success, and 1 on failure.
 */
int draw_game_mouse();

/**
 * @brief Displays the game timer.
 * 
 * This function displays the game timer on the screen. It takes the current game
 * time in seconds as input and converts it into a format suitable for display.
 * The game timer is drawn using digit sprites, with each digit representing
 * a different place value (hundreds, tens, units).
 * 
 * @param game_seconds The current game time in seconds.
 */
void display_game_timer(int game_seconds);

#endif // GAME_H


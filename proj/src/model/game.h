#ifndef GAME_H
#define GAME_H

#include "../model/board.h"


/**
 * @brief Handles mouse input during the game.
 *
 * @param b The game board.
 */
void mouse_game_handler(Board* b);

/**
 * @brief Handles keyboard input during the game.
 *
 * @param b The game board.
 */
void keyboard_game_handler(Board* b);

/**
 * @brief Handles the game timer logic.
 *
 * @param b The game board.
 */
void timer_game_handler(Board* b);

/**
 * @brief Checks if the player has won the game.
 *
 * @param b The game board.
 */
void check_game_win(Board* b);

/**
 * @brief Draws the game window when the player wins.
 *
 * @param b The game board.
 * @return 0 on success, 1 on failure.
 */
int draw_game_win(Board* b);

/**
 * @brief Draws the mouse cursor for the game.
 *
 * @return 0 on success, 1 on failure.
 */
int draw_game_mouse();

/**
 * @brief Draws the game timer on the screen.
 *
 * @param x The x-coordinate of the timer.
 * @param y The y-coordinate of the timer.
 * @return 0 on success, 1 on failure.
 */
int draw_game_timer(int x, int y);

/**
 * @brief Draws the game board on the screen.
 *
 * @param b The game board.
 * @return 0 on success, 1 on failure.
 */
int draw_game_board(Board* b);

/**
 * @brief Draws the game tiles on the screen.
 *
 * @param b The game board.
 * @return 0 on success, 1 on failure.
 */
int draw_game_tiles(Board* b);

/**
 * @brief Draws the game hints on the screen.
 *
 * @param b The game board.
 * @return 0 on success, 1 on failure.
 */
int draw_game_hints(Board* b);

/**
 * @brief Displays the game timer on the screen.
 *
 * @param game_seconds The elapsed game time in seconds.
 */
void display_game_timer(int game_seconds);

#endif // GAME_H


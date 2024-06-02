#ifndef _INFO_H_
#define _INFO_H_

#include <stdint.h>

/** @defgroup info info
 * @{
 * 
 * Constants for the game.
 */

#define GAME_MODE 0x115/**< @brief Game video graphics mode */
#define GAME_FPS 60 /**< @brief Game frames per second */
#define CONSOLE_WIDTH_115 800 /**< @brief Number of horizontal pixels */
#define CONSOLE_HEIGHT_115 600 /**< @brief Number of vertical pixels */
#define CONSOLE_WIDTH 1152 /**< @brief Number of horizontal pixels */
#define CONSOLE_HEIGHT 864 /**< @brief Number of vertical pixels */

#define GAME_HEIGHT 28

#define MAIN_MENU_X_ORIGIN 350 /**< @brief Starting x position for the menu */
#define MAIN_MENU_Y_ORIGIN 150 /**< @brief Starting y position for the menu */


#define KEY_W 0x91 /**< @brief Scancode break byte for key 'w' */
#define KEY_S 0x9f /**< @brief Scancode break byte for key 's' */
#define KEY_SPACE 0xB9 /**< @brief Scancode break byte for key 'space' */
#define KEY_3 0x84 /**< @brief Scancode make byte for key '3' */
#define KEY_2 0x83 /**< @brief Scancode make byte for key '2' */
#define KEY_1 0x82 /**< @brief Scancode break byte for key '1' */
#define KEY_0 0x8b /**< @brief Scancode break byte for key '0' */

#define KEY_ESC 0x01 /**< @brief Scancode make byte for key 'ESC' */


#define NUMBER_WIDTH 40 /**< @brief Horizontal pixels of an number */
#define NUMBER_HEIGHT 31 /**< @brief Vertical pixels of an number */


#define COLOR_WHITE 0xFFFFFF
#define COLOR_BLUE 0xADD8E6
#define COLOR_BLACK 0x000000
#define COLOR_YELLOW 0xFFFF00

#define TILE_SIZE 45
#define MOUSE_WIDTH 17
#define MOUSE_HEIGHT 23

/**
 * @brief Enumeration representing the possible states of the game menu.
 */
typedef enum {
    MENU,           /**< The main menu state. */
    RULES,          /**< The rules menu state. */
    CHOOSE_GAME,    /**< The state for choosing the game. */
    GAME,           /**< The state representing the gameplay. */
    LEAVE,          /**< The state for leaving the game. */
    GAME_WIN        /**< The state representing the game win condition. */
} MenuState;

/**@}*/

#endif /* _INFO_H */

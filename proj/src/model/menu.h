#ifndef _MENU_H_
#define _MENU_H_

#include <lcom/lcf.h>

#include "./controller/timer.h"
#include "./controller/graphics.h"
#include "info.h"
#include "sprites.h"
#include "board.h"
#include "game.h"


typedef enum {
    MENU,
    RULES,
    CHOOSE_GAME,
    GAME
} MenuState;

/**
 * @brief Handles keyboard input for the menu.
 *
 * This function processes keyboard input for the menu and determines whether to continue or exit the menu.
 *
 * @return Returns true to continue processing, and false to exit the menu.
 */
bool (keyboard_menu_handler)();

/**
 * @brief Displays the main menu.
 *
 * This function clears the screen, draws the main menu background and elements, and refreshes the graphics content.
 *
 * @return Returns 0 on success, and 1 on failure.
 */
int (displayMainMenu)();

/**
 * @brief Displays the rules menu.
 *
 * This function clears the screen, draws the main menu background and elements, and refreshes the graphics content.
 *
 * @return Returns 0 on success, and 1 on failure.
 */
int (displayRules)();

/**
 * @brief Displays the choose game menu.
 *
 * This function clears the screen, draws the main menu background and elements, and refreshes the graphics content.
 *
 * @return Returns 0 on success, and 1 on failure.
 */
int (displayChooseGame)();

/**@}*/

#endif /* _MENU_H */


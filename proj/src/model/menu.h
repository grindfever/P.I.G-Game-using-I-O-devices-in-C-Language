#ifndef _MENU_H_
#define _MENU_H_

#include <lcom/lcf.h>

#include "./controller/timer.h"
#include "./controller/graphics.h"
#include "info.h"
#include "sprites.h"
#include "board.h"
#include "game.h"

/**
 * @brief Handles keyboard input during the main menu.
 */
void keyboard_menu_handler();

/**
 * @brief Handles keyboard input for default actions in menus.
 */
void keyboard_default_handler();

/**
 * @brief Handles default mouse events.
 */
void mouse_default_handler();

/**
 * @brief Displays the main menu.
 *
 * @return 0 on success, 1 on failure.
 */
int displayMainMenu();

/**
 * @brief Displays the rules menu.
 *
 * @return 0 on success, 1 on failure.
 */
int displayRules();

/**@}*/

#endif /* _MENU_H */


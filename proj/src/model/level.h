#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <lcom/lcf.h>

#include "./controller/timer.h"
#include "./controller/graphics.h"
#include "info.h"
#include "sprites.h"
#include "board.h"
#include "game.h"

/**
 * @brief Handles keyboard input for the menu.
 *
 * This function processes keyboard input for the menu and determines whether to continue or exit the menu.
 *
 */
void (keyboard_level_handler)();

/**
 * @brief Displays the choose game menu.
 *
 * This function clears the screen, draws the main menu background and elements, and refreshes the graphics content.
 *
 * @return Returns 0 on success, and 1 on failure.
 */
int (displayChooseGame)();


/**@}*/

#endif /* _LEVEL_H */

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
 * @brief Handles keyboard input during level selection.
 */
void keyboard_level_handler();

/**
 * @brief Displays the menu for choosing the game level.
 *
 * @return 0 on success, 1 on failure.
 */
int displayChooseGame();

/**@}*/

#endif /* _LEVEL_H */

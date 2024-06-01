#include <lcom/lcf.h>

#include <stdint.h>

#include "menu.h"
#include "./controller/keyboard.h"
#include "./controller/I8042.h"

extern bool keyboard_complete;
extern struct scan_code_stats scan_code;

extern MenuState menu_state;
extern Board* b;


void (keyboard_level_handler)() {
    kbc_ih();
    if (keyboard_complete) {
        switch(scan_code.code[scan_code.size - 1]){
            case KBC_BREAK_ESC:
                menu_state = MENU;
                break;
            case KEY_1:
                menu_state = GAME;
                b = construct_board(250,250,3);
                break;
            case KEY_2:
                menu_state = GAME;
                b = construct_board(250,150,5);
                break;
            case KEY_3:
                menu_state = GAME;
                b = construct_board(300,200,7);
                break;
        }
    }
}

int displayChooseGame() {
    clear_graphics_screen();

    for (int i = 0; i < CONSOLE_WIDTH_115; ++i) {
        for (int j = 0; j < CONSOLE_HEIGHT_115; ++j) {
            if (generate_pixel(i, j, COLOR_BLUE)) {
                return 1;
            }
        }
    }

    struct MenuElement {
        const xpm_row_t* sprite;
        int x_offset;
        int y_offset;
    };

    struct MenuElement elements[] = {
        {sprite_1, -50, -50},
        {main_menu_sprite_esc, 50, -50},
        {sprite_2, -50, 50},
        {main_menu_sprite_esc, 50, 50},
        {sprite_3, -50, 150},
        {main_menu_sprite_esc, 50, 150}
        
    };

    // Draw all menu elements
    size_t num_elements = sizeof(elements) / sizeof(elements[0]);
    for (size_t i = 0; i < num_elements; ++i) {
        struct MenuElement elem = elements[i];
        if (draw_element(elem.sprite, MAIN_MENU_X_ORIGIN + elem.x_offset, MAIN_MENU_Y_ORIGIN + elem.y_offset)) {
            return 1;
        }
    }

    draw_graphics_content();

    return 0;
}

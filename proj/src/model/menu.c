#include <lcom/lcf.h>

#include <stdint.h>

#include "menu.h"
#include "./controller/keyboard.h"
#include "./controller/I8042.h"

extern bool keyboard_complete;
extern struct scan_code_stats scan_code;

extern MenuState menu_state;
extern Board* b;

void (keyboard_menu_handler)() {
    kbc_ih();
    if (keyboard_complete) {
        switch(scan_code.code[scan_code.size - 1]){
            case KBC_BREAK_ESC:
                switch(menu_state){
                    case RULES:
                        menu_state = MENU;
                        return;
                        break;
                    case MENU:
                        menu_state = LEAVE;
                        break;
                    case GAME:
                        menu_state = CHOOSE_GAME;
                        destroy_board(b);
                        break;
                    default:
                        break;
                }
                break;
            case KEY_1:
                if(menu_state == MENU){
                    menu_state = CHOOSE_GAME;
                    return;
                }
                break;
            case KEY_2:
                if(menu_state == MENU){
                    menu_state = RULES;
                    return;
                }
                break;
        }
    }
}

int displayMainMenu() {
    clear_graphics_screen();

    // Draw background pixels
    for (int i = 0; i < CONSOLE_WIDTH_115; ++i) {
        for (int j = 0; j < CONSOLE_HEIGHT_115; ++j) {
            if (generate_pixel(i, j, COLOR_BLUE)) {
                return 1;
            }
        }
    }


    // Define menu elements with their respective positions using a struct tag
    struct MenuElement {
        const xpm_row_t* sprite;
        int x_offset;
        int y_offset;
    };

    struct MenuElement elements[] = {
        {main_menu_sprite_P, -100, -50},
        {main_menu_sprite_I, -50, -50},
        {main_menu_sprite_C, 0, -50},
        {main_menu_sprite_R, 50, -50},
        {main_menu_sprite_O, 100, -50},
        {main_menu_sprite_S, 150, -50},
        {main_menu_sprite_S, 200, -50},
        {sprite_1, -80, 50},
        {main_menu_sprite_P, 0, 50},
        {main_menu_sprite_L, 50, 50},
        {main_menu_sprite_A, 100, 50},
        {main_menu_sprite_Y, 150, 50},
        {sprite_2, -80, 150},
        {main_menu_sprite_R, 0, 150},
        {main_menu_sprite_U, 50, 150},
        {main_menu_sprite_L, 100, 150},
        {main_menu_sprite_E, 150, 150},
        {main_menu_sprite_S, 200, 150},
        {sprite_0, -80, 250},
        {main_menu_sprite_E, 0, 250},
        {main_menu_sprite_X, 50, 250},
        {main_menu_sprite_I, 100, 250},
        {main_menu_sprite_T, 150, 250}
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


int displayRules() {
    clear_graphics_screen();

    // Draw background pixels
    for (int i = 0; i < CONSOLE_WIDTH_115; ++i) {
        for (int j = 0; j < CONSOLE_HEIGHT_115; ++j) {
            if (generate_pixel(i, j, COLOR_BLUE)) {
                return 1;
            }
        }
    }


    // Define menu elements with their respective positions using a struct tag
    struct MenuElement {
        const xpm_row_t* sprite;
        int x_offset;
        int y_offset;
    };

    struct MenuElement elements[] = {
        {main_menu_sprite_H, -200, -50},
        {main_menu_sprite_O, -150, -50},
        {main_menu_sprite_T, -50, -50},
        {main_menu_sprite_O, 0, -50},
        {main_menu_sprite_P, 50, -50},
        {main_menu_sprite_L, 100, -50},
        {main_menu_sprite_A, 150, -50},
        {main_menu_sprite_Y, 200, -50}
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

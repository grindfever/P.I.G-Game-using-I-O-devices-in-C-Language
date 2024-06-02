#include <lcom/lcf.h>

#include <stdint.h>

#include "menu.h"
#include "./controller/keyboard.h"
#include "./controller/I8042.h"

extern bool keyboard_complete;
extern struct scan_code_stats scan_code;

extern MenuState menu_state;
extern Board* b;

int selected_level = 0;
int buttons_level = 3;

void (keyboard_level_handler)() {
    kbc_ih();
    if (keyboard_complete) {
        switch(scan_code.code[scan_code.size - 1]){
            case KBC_BREAK_ESC:
                menu_state = MENU;
                break;
            case KEY_S:
                selected_level += 1;
                if(selected_level >= buttons_level){
                    selected_level = 0;
                }
                break;
            case KEY_W:
                selected_level -= 1;
                if(selected_level < 0){
                    selected_level = buttons_level - 1;
                }
                break;
            case KEY_SPACE:
                switch (selected_level){
                    case 0:
                        menu_state = GAME;
                        b = construct_board(250,250,3);
                        break;
                    case 1:
                        menu_state = GAME;
                        b = construct_board(250,250,5);
                        break;
                    case 2:
                        menu_state = GAME;
                        b = construct_board(500,200,7);
                        break;
                }
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

    const xpm_row_t* button1 = button_back_off_sprite;
    const xpm_row_t* button2 = button_back_off_sprite;
    const xpm_row_t* button3 = button_back_off_sprite;

    switch(selected_level){
        case 0:
            button1 = button_back_on_sprite;
            break;
        case 1:
            button2 = button_back_on_sprite;
            break;
        case 2:
            button3 = button_back_on_sprite;
            break;
        default:
            break;
    }

    struct MenuElement elements[] = {
        {button1, 263, 100},
        {sprite_E, 323, 120},
        {sprite_A, 363, 120},
        {sprite_S, 403, 120},
        {sprite_Y, 443, 120},
        {button2, 263, 250},
        {sprite_M, 285, 270},
        {sprite_E, 325, 270},
        {sprite_D, 365, 270},
        {sprite_I, 405, 270},
        {sprite_U, 445, 270},
        {sprite_M, 483, 270},
        {button3, 263, 400},
        {sprite_H, 323, 420},
        {sprite_A, 363, 420},
        {sprite_R, 403, 420},
        {sprite_D, 443, 420},
    };

    size_t num_elements = sizeof(elements) / sizeof(elements[0]);
    for (size_t i = 0; i < num_elements; ++i) {
        struct MenuElement elem = elements[i];
        if (draw_element(elem.sprite, elem.x_offset, elem.y_offset)) {
            return 1;
        }
    }

    draw_graphics_content();

    return 0;
}

#include <lcom/lcf.h>

#include <stdint.h>

#include "menu.h"
#include "controller/mouse.h"
#include "controller/keyboard.h"
#include "controller/I8042.h"

extern bool keyboard_complete;
extern struct scan_code_stats scan_code;
extern bool mouse_complete;
extern struct packet pack;

extern MenuState menu_state;

int selected = 0;
int buttons = 2;

void mouse_default_handler(){
    mouse_ih();
    if(mouse_complete){
        return;
    }
}

void (keyboard_menu_handler)() {
    kbc_ih();
    if (keyboard_complete) {
        switch(scan_code.code[scan_code.size - 1]){
            case KBC_BREAK_ESC:
                menu_state = LEAVE;
                break;
            case KEY_S:
                selected += 1;
                if(selected >= buttons){
                    selected = 0;
                }
                break;
            case KEY_W:
                selected -= 1;
                if(selected < 0){
                    selected = buttons - 1;
                }
                break;
            case KEY_SPACE:
                switch (selected){
                    case 0:
                        menu_state = CHOOSE_GAME;
                        break;
                    case 1:
                        menu_state = RULES;
                        break;

                }
                break;
        }
    }
}

void keyboard_default_handler(){
    kbc_ih();
    if (keyboard_complete) {
        switch(scan_code.code[scan_code.size - 1]){
            case KBC_BREAK_ESC:
                menu_state = MENU;
                break;
        }
    }
}

int displayMainMenu() {
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

    switch(selected){
        case 0:
            button1 = button_back_on_sprite;
            break;
        case 1:
            button2 = button_back_on_sprite;
            break;
        default:
            break;
    }

    struct MenuElement elements[] = {
        {sprite_logo, 200, 100},
        {button1, 263, 300},
        {sprite_P, 323, 320},
        {sprite_L, 363, 320},
        {sprite_A, 403, 320},
        {sprite_Y, 443, 320},
        {button2, 263, 400},
        {sprite_R, 303, 420},
        {sprite_U, 343, 420},
        {sprite_L, 383, 420},
        {sprite_E, 423, 420},
        {sprite_S, 463, 420},
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
        {sprite_H, -200, -50},
        {sprite_O, -150, -50},
        {sprite_T, -50, -50},
        {sprite_O, 0, -50},
        {sprite_P, 50, -50},
        {sprite_L, 100, -50},
        {sprite_A, 150, -50},
        {sprite_Y, 200, -50}
    };

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

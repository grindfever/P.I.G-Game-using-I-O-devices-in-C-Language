#include <lcom/lcf.h>

#include <stdint.h>

#include "menu.h"
#include "controller/keyboard.h"
#include "controller/I8042.h"

extern bool keyboard_complete;
extern struct scan_code_stats scan_code;

extern int irq_set_kbd;

bool (keyboard_menu_handler)() {
    kbc_ih();
    if (keyboard_complete) {

        printf("scan %d\n", scan_code.code[scan_code.size - 1]);

        if(scan_code.code[scan_code.size - 1] == KBC_BREAK_ESC) {
            printf("reached");
            return false;
        }

        /*
        if (!kbc_inc_code()) {
            key_code = get_key_code();
                            
            if (key_code == KEY_1) {
            }
            else if (key_code == KEY_2){
            }
            else if (key_code == KEY_0)
                process = 0;
        }
        */

    }

    return true;
}

// ----------------------------------------------------------------------------------------
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
        {main_menu_sprite_P, -100, -100},
        {main_menu_sprite_I, -50, -100},
        {main_menu_sprite_C, 0, -100},
        {main_menu_sprite_R, 50, -100},
        {main_menu_sprite_O, 100, -100},
        {main_menu_sprite_S, 150, -100},
        {main_menu_sprite_S, 200, -100},
        {main_menu_sprite_1, -80, 0},
        {main_menu_sprite_P, 0, 0},
        {main_menu_sprite_L, 50, 0},
        {main_menu_sprite_A, 100, 0},
        {main_menu_sprite_Y, 150, 0},
        {main_menu_sprite_2, -80, 50},
        {main_menu_sprite_R, 0, 50},
        {main_menu_sprite_U, 50, 50},
        {main_menu_sprite_L, 100, 50},
        {main_menu_sprite_E, 150, 50},
        {main_menu_sprite_S, 200, 50},
        {main_menu_sprite_0, -80, 50},
        {main_menu_sprite_E, 0, 100},
        {main_menu_sprite_X, 50, 100},
        {main_menu_sprite_I, 100, 100},
        {main_menu_sprite_T, 150, 100}
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






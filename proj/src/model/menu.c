#include <lcom/lcf.h>

#include <stdint.h>

#include "menu.h"



int (main_menu)() {
    if (start()) 
        return 1;
        
    int r, ipc_status;
    message msg;

    uint8_t key_code = 0;
    int process = 1;
    while (process) {
        if (displayMainMenu())
            return 1;

        /* Get a request message. */
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("driver_receive failed with: %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) { // received notification
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE: // hardware interrupt notification
                    if (msg.m_notify.interrupts & irq_set_kbd) { // subscribed interrupt
                        kbc_ih();

                        if (!kbc_inc_code()) {
                            key_code = get_key_code();
                            
                            if (key_code == KEY_1) {
                            }
                            else if (key_code == KEY_2){
                            }
                            else if (key_code == KEY_0)
                                process = 0;
                        }
                    }
                    
                    break;
                default:
                    break; // no other notifications expected: do nothing
            }
        }
        if (msg.m_notify.interrupts & irq_set_mouse) { // subscribed interrupt (Mouse)
            mouse_ih();
            if (mouse_check_full() && !mouse_overflow()) {

                  
            }
        }  
        else { // received a standard message, not a notification
            // no standard messages expected: do nothing
        }
    }

    if (end())
        return 1;

    return 0;
}



// ----------------------------------------------------------------------------------------
int displayMainMenu() {
    clear_graphics_screen();

    // Draw background pixels
    for (int i = 0; i < CONSOLE_WIDTH; ++i) {
        for (int j = 0; j < CONSOLE_HEIGHT; ++j) {
            if (generate_pixel(i, j, 3)) {
                if (end()) {
                    return 1;
                }
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
        {main_menu_sprite_P, -100, -180},
        {main_menu_sprite_I, -50, -180},
        {main_menu_sprite_C, 0, -180},
        {main_menu_sprite_R, 50, -180},
        {main_menu_sprite_O, 100, -180},
        {main_menu_sprite_S, 150, -180},
        {main_menu_sprite_S, 200, -180},
        {main_menu_sprite_1, -80, 0},
        {main_menu_sprite_P, 0, 0},
        {main_menu_sprite_L, 50, 0},
        {main_menu_sprite_A, 100, 0},
        {main_menu_sprite_Y, 150, 0},
        {main_menu_sprite_2, -80, 100},
        {main_menu_sprite_R, 0, 100},
        {main_menu_sprite_U, 50, 100},
        {main_menu_sprite_L, 100, 100},
        {main_menu_sprite_E, 150, 100},
        {main_menu_sprite_S, 200, 100},
        {main_menu_sprite_0, -80, 200},
        {main_menu_sprite_E, 0, 200},
        {main_menu_sprite_X, 50, 200},
        {main_menu_sprite_I, 100, 200},
        {main_menu_sprite_T, 150, 200}
    };

    // Draw all menu elements
    size_t num_elements = sizeof(elements) / sizeof(elements[0]);
    for (size_t i = 0; i < num_elements; ++i) {
        struct MenuElement elem = elements[i];
        if (draw_element(elem.sprite, MAIN_MENU_X_ORIGIN + elem.x_offset, MAIN_MENU_Y_ORIGIN + elem.y_offset)) {
            if (end()) {
                // Separate and explicit handling for leave
                return 1;
            }
            return 1;
        }
    }

    draw_graphics_content();

    return 0;
}






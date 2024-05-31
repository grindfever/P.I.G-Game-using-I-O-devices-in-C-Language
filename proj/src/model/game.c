#include <lcom/lcf.h>

#include <stdint.h>

#include "controller/mouse.h"
#include "controller/I8042.h"
#include "controller/graphics.h"
#include "board.h"
#include "sprites.h"
#include "info.h"

extern bool mouse_complete;
extern struct packet pack;

int mouse_x = 5;
int mouse_y = 5;
bool clicking = false;

void mouse_game_handler(Board* b){
    mouse_ih();
    if (mouse_complete) {

        //update mouse position
        if (!pack.x_ov) {
            mouse_x += pack.delta_x;
            if(mouse_x < 0){
                mouse_x = 0;
            }
        }
        if (!pack.y_ov) {
            mouse_y -= pack.delta_y; 
            if(mouse_y < 0){
                mouse_y = 0;
            }
        }

        //if left pressed, change board (currently on position (0,0) and tile size 10)
        if (pack.lb) {
            if(mouse_x > b->x && mouse_x < b->x + b->size*50 && mouse_y > b->y && mouse_y < b->y + b->size*50){
                uint8_t tile_pos_x = (mouse_x - b->x)/ 50;
                uint8_t tile_pos_y = (mouse_y - b->y)/ 50;
                toggle_board_tile(tile_pos_x, tile_pos_y, b);
                print_board(b);
            }
            clicking = true;
        }
        else {
            clicking = false;
        }
    }
}

int draw_game_mouse(){
    static xpm_row_t* to_draw;
    
    if(clicking){
        to_draw = mouse_sprite_click;
    }
    else {
        to_draw = mouse_sprite;
    }

    if (draw_element(to_draw, mouse_x, mouse_y)) {
        return 1;
    }

    return 0;
}

int draw_game_board(Board* b) {
    clear_graphics_screen();

    // Draw background pixels
    for (int i = 0; i < CONSOLE_WIDTH_115; ++i) {
        for (int j = 0; j < CONSOLE_HEIGHT_115; ++j) {
            if (generate_pixel(i, j, COLOR_BLUE)) {
                return 1;
            }
        }
    }

    for(int i = 0; i < b->size; i++){
        for(int j = 0; j < b->size; j++){
            static xpm_row_t* to_draw;

            if(b->tiles[j][i].on){
                to_draw = tile_sprite_on;
            }
            else {
                to_draw = tile_sprite_off;
            }

            if (draw_element(to_draw, b->x + j*50, b->y + i*50)) {
                return 1;
            }
        }
    }

    if(draw_game_mouse()){
        return 1;
    }

    draw_graphics_content();

    return 0;
}

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

static xpm_row_t* number_sprites[10] = {sprite_0, sprite_1, sprite_2, sprite_3, sprite_4, sprite_5, sprite_6, sprite_7, sprite_8, sprite_9};

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
            clicking = true;
        }
        else {
            if(mouse_x > b->x && mouse_x < b->x + b->size*TILE_SIZE && mouse_y > b->y && mouse_y < b->y + b->size*TILE_SIZE && clicking){
                uint8_t tile_pos_x = (mouse_x - b->x)/ TILE_SIZE;
                uint8_t tile_pos_y = (mouse_y - b->y)/ TILE_SIZE;
                toggle_board_tile(tile_pos_x, tile_pos_y, b);
            }
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

int draw_game_tiles(Board* b){
    for(int i = 0; i < b->size; i++){
        for(int j = 0; j < b->size; j++){
            static xpm_row_t* to_draw;

            if(b->tiles[j][i].on){
                to_draw = tile_sprite_on;
            }
            else {
                to_draw = tile_sprite_off;
            }

            if (draw_element(to_draw, b->x + j*TILE_SIZE, b->y + i*TILE_SIZE)) {
                return 1;
            }
        }
    }
    return 0;
}

int draw_game_hints(Board* b){
    for(int i = 0; i < b->size; i++){
        Hint* current_h = b->h_hints[i];

        int counter = 1;

        while (current_h != NULL) {
            if(current_h->count != 0){
                if(draw_element(number_sprites[current_h->count], b->x - counter*TILE_SIZE, b->y + i*TILE_SIZE + 5)){
                    return 1;
                }
                counter += 1;
            }
            current_h = current_h->next;
        }
    }

    for(int i = 0; i < b->size; i++){
        Hint* current_v = b->v_hints[i];

        int counter = 1;

        while (current_v != NULL) {
            if(current_v->count != 0){
                if(draw_element(number_sprites[current_v->count], b->x + i*TILE_SIZE + 5, b->y - counter*TILE_SIZE)){
                    return 1;
                }
                counter += 1;
            }
            current_v = current_v->next;
        }
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

    if(draw_game_tiles(b)){
        return 1;
    }

    if(draw_game_hints(b)){
        return 1;
    }

    if(draw_game_mouse()){
        return 1;
    }

    draw_graphics_content();

    return 0;
}

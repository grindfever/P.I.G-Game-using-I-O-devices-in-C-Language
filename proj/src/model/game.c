#include <lcom/lcf.h>

#include <stdint.h>

#include "controller/mouse.h"
#include "controller/keyboard.h"
#include "controller/I8042.h"
#include "controller/graphics.h"
#include "board.h"
#include "sprites.h"
#include "info.h"

extern bool mouse_complete;
extern struct packet pack;
extern bool keyboard_complete;
extern struct scan_code_stats scan_code;
extern MenuState menu_state;

int mouse_x = 200;
int mouse_y = 200;
int minutes = 0;
int seconds = 0;
int time_counter = 0;
bool clicking = false;

static xpm_row_t* number_sprites[10] = {sprite_0, sprite_1, sprite_2, sprite_3, sprite_4, sprite_5, sprite_6, sprite_7, sprite_8, sprite_9};

void (keyboard_game_handler)(Board* b) {
    kbc_ih();

    if (keyboard_complete) {
        if(scan_code.code[scan_code.size - 1] == KBC_BREAK_ESC){
            menu_state = CHOOSE_GAME;
            destroy_board(b);
            minutes = 0;
            seconds = 0;
            clicking = false;
            mouse_x = 200;
            mouse_y = 200;
        }
    }
}

void check_game_win(Board* b){
    if(check_win(b)){
      menu_state = GAME_WIN;
    }
}

void mouse_game_handler(Board* b){
    mouse_ih();
    if (mouse_complete) {

        //update mouse position
        if (!pack.x_ov) {
            mouse_x += pack.delta_x;
            if(mouse_x < 0){
                mouse_x = 0;
            }
            if(mouse_x > CONSOLE_WIDTH_115 - MOUSE_WIDTH){
                mouse_x = CONSOLE_WIDTH_115 - MOUSE_WIDTH;
            }
        }
        if (!pack.y_ov) {
            mouse_y -= pack.delta_y; 
            if(mouse_y < 0){
                mouse_y = 0;
            }
            if(mouse_y > CONSOLE_HEIGHT_115 - MOUSE_HEIGHT){
                mouse_y = CONSOLE_HEIGHT_115 - MOUSE_HEIGHT;
            }
        }

        if (pack.lb) {
            clicking = true;
        }
        else {
            if(mouse_x+4 > b->x && mouse_x+4 < b->x + b->size*TILE_SIZE && mouse_y > b->y && mouse_y < b->y + b->size*TILE_SIZE && clicking){
                uint8_t tile_pos_x = (mouse_x - b->x)/ TILE_SIZE;
                uint8_t tile_pos_y = (mouse_y - b->y)/ TILE_SIZE;
                toggle_board_tile(tile_pos_x, tile_pos_y, b);
            }
            clicking = false;
        }
    }
}

void timer_game_handler(Board* b){
    if(minutes == 60){
        return;
    }

    time_counter += 2;

    if(time_counter % 60 == 0){
        time_counter = 0;
        seconds += 1;
        if(seconds % 60 == 0){
            seconds = 0;
            minutes += 1;
        }
    }
}

int draw_game_timer(int x, int y){
    int temp_s = seconds;
    int temp_m = minutes;

    int pos = 0;

    for(int i = 0; i < 2; i++){
        if (draw_element(number_sprites[temp_s%10], x+124-pos*31 , y)) {
            return 1;
        }
        temp_s /= 10;
        pos += 1;
    }

    if (draw_element(sprite_double_dot, x+124-pos*31 , y)) {
        return 1;
    }

    pos += 1;

    for(int i = 0; i < 2; i++){
        if (draw_element(number_sprites[temp_m%10], x+124-pos*31 , y)) {
            return 1;
        }
        temp_m /= 10;
        pos += 1;
    }

    return 0;
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
                if(draw_element(number_sprites[current_h->count], b->x - counter*TILE_SIZE + 7, b->y + i*TILE_SIZE + 5)){
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
                if(draw_element(number_sprites[current_v->count], b->x + i*TILE_SIZE + 5, b->y - counter*TILE_SIZE + 7)){
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

    for (int i = 0; i < CONSOLE_WIDTH_115; ++i) {
        for (int j = 0; j < CONSOLE_HEIGHT_115; ++j) {
            if (generate_pixel(i, j, COLOR_BLUE)) {
                return 1;
            }
        }
    }

    if(draw_game_timer(CONSOLE_WIDTH_115-155-10, 10)){ //155 -> 5*31(width of number sprite)
        return 1;
    }

    if(draw_element(main_menu_sprite_esc, 10, 10)){
        return 1;
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


int draw_game_win(Board* b) {
    clear_graphics_screen();

    for (int i = 0; i < CONSOLE_WIDTH_115; ++i) {
        for (int j = 0; j < CONSOLE_HEIGHT_115; ++j) {
            if (generate_pixel(i, j, COLOR_BLUE)) {
                return 1;
            }
        }
    }

    if(draw_game_timer(320, 80)){ //155 -> 5*31(width of number sprite)
        return 1;
    }

    if(draw_element(main_menu_sprite_esc, 10, 10)){
        return 1;
    }

    if(draw_element(sprite_Y, 220, 20)){
        return 1;
    }
    if(draw_element(sprite_O, 270, 20)){
        return 1;
    }
    if(draw_element(sprite_U, 320, 20)){
        return 1;
    }
    if(draw_element(sprite_W, 420, 20)){
        return 1;
    }
    if(draw_element(sprite_O, 470, 20)){
        return 1;
    }
    if(draw_element(sprite_N, 520, 20)){
        return 1;
    }

    if(draw_game_tiles(b)){
        return 1;
    }

    if(draw_game_hints(b)){
        return 1;
    }

    draw_graphics_content();

    return 0;
}

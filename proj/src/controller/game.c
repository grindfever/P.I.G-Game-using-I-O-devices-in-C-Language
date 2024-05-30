#include <lcom/lcf.h>

#include <stdint.h>

#include "controller/mouse.h"
#include "controller/I8042.h"
#include "../model/board.h"
#include "sprites.h"
#include "graphics.h"

extern bool mouse_complete;
extern struct packet pack;

int mouse_x = 5;
int mouse_y = 5;

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
            if(mouse_x > b->x && mouse_x < b->x + b->size*10 && mouse_y > b->y && mouse_y < b->y + b->size*10){
                uint8_t tile_pos_x = mouse_x / 10;
                uint8_t tile_pos_y = mouse_y / 10;
                toggle_board_tile(tile_pos_x, tile_pos_y, b);
                print_board(b);
            }
        }

        printf("Mouse Position: (%d, %d)\n", mouse_x, mouse_y);
    }
}

   void display_game_timer(int game_seconds){
        countdown=300-game_seconds;//podemos alterar isto para nao ser sempre 5 minutos
        int x1=0,x2=0,x3=0;        //podemos passar como argumento a dificuldade ou assim 

        if (countdown <= 0) {
                // Set all digits to 0 if countdown has ended
                draw_digit(0, 10, 10);  
                draw_digit(0, 30, 10);  
                draw_digit(0, 50, 10);  
            } else {

        x1 = countdown / 100;        // Extract the hundreds place
        x2 = (countdown / 10) % 10; // Extract the tens place
        x3 = countdown % 10;       // Extract the units place
        
        // Define positions for the digits (adjust based on your screen layout)
        uint16_t x_position = 10; // Starting x position for the first digit
        uint16_t y_position = 10; // Starting y position for the digits

        // Draw the digits
        draw_digit(x1, x_position, y_position);
        draw_digit(x2, x_position + 20, y_position); 
        draw_digit(x3, x_position + 40, y_position); 

        // Refresh the graphics content
        draw_graphics_content();
        
    }
   }
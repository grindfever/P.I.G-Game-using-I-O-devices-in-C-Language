// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>
#include "controller/keyboard.h"
#include "controller/mouse.h"
#include "controller/game.h"
#include "controller/menu.h"
#include "controller/I8042.h"
#include "./controller/graphics.h"
#include "model/board.h"
#include "model/tile.h"

// Any header files included below this line should have been created by you
#include "controller/keyboard.h"
#include "controller/mouse.h"
#include "controller/game.h"
#include "controller/menu.h"
#include "controller/I8042.h"
#include "./controller/graphics.h"
#include "model/board.h"
#include "model/tile.h"

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/proj/output/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/proj/output/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int irq_set_timer = 0;
int irq_set_kbd = 0;
int irq_set_mouse = 0;

/**
 * @brief Initializes the system by subscribing to interrupts and setting up the video mode.
 * 
 * @return 0 on success, 1 on failure.
 */
int start(){
  uint8_t bit_no_kbd;
  uint8_t bit_no_timer;
  uint8_t bit_no_mouse;
  int check;

  if(keyboard_subscribe_int(&bit_no_kbd)){
    return 1;
  }

  for(int i = 0; i < 2; i++){
    check = mouse_send_command(KBC_EN_REP);
    if(check == 0){
      break;
    }
  }

  if(check){
    return 1;
  }

  if(mouse_subscribe_int(&bit_no_mouse)){
    return 1;
  }

  if(timer_subscribe_int(&bit_no_timer)){
    return 1;
  }
  if (timer_set_frequency(0, 60)) {
    return 1;
  }

  if (vg_init(GAME_MODE) == NULL){
    return 1;
  }

  irq_set_kbd = BIT(bit_no_kbd);
  irq_set_mouse = BIT(bit_no_mouse);
  irq_set_timer = BIT(bit_no_timer);

  return 0;
}

/**
 * @brief Cleans up the system by unsubscribing from interrupts and exiting the video mode.
 * 
 * @return 0 on success, 1 on failure.
 */
int end(){
  int check;

  if (vg_exit() != OK){
    return 1;
  }

  if(keyboard_unsubscribe_int()){
    return 1;
  }

  if(mouse_unsubscribe_int()){
    return 1;
  }

  for(int i = 0; i < 2; i++){
    check = mouse_send_command(KBC_DIS_REP);
    if(check == 0){
      break;
    }
  }

  if(timer_unsubscribe_int()){
    return 1;
  }

  return 0;
}

int loop(){
  message msg;
  int ipc_status;
  int r;
  int menu = 1;
  bool continue_loop = 1;

  Board* b = construct_board(0,0,5);

  while( continue_loop ) {
    
    if(menu){
      if (displayMainMenu()) return 1;
    }

    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:	
          if (msg.m_notify.interrupts & irq_set_mouse) {
            if(menu){}
            else {
              mouse_game_handler(b); 
            }
          }
          if (msg.m_notify.interrupts & irq_set_kbd) { 
            if(menu){ //depois pode ser um switch se tiver mais estados
              continue_loop = keyboard_menu_handler(); 
            }
            else {}
          }
          if (msg.m_notify.interrupts & irq_set_timer) {
            timer_int_handler();
            if(!menu){
              timer_counter++;
              if (timer_counter % 60 == 0) {
              game_seconds++;
              }
              display_game_timer(game_seconds);
          
             }
          }
        default:
          break;
      }
    } 
  }

                
                              }
  destroy_board(b);

  return 0;
}

int (proj_main_loop)(int argc, char **argv) {
  if(start()){
    return 1;
  }

  if (loop()){
    return 1;
  }

  if(end()){
    return 1;
  }

  return 0;
}

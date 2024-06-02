// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you
#include "controller/keyboard.h"
#include "controller/mouse.h"
#include "controller/I8042.h"
#include "controller/graphics.h"
#include "model/board.h"
#include "model/tile.h"
#include "model/game.h"
#include "model/level.h"
#include "model/menu.h"

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
Board* b;

MenuState menu_state = MENU;

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
  if (timer_set_frequency(0, 30)) {
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

/**
 * @brief Main event loop of the program.
 * 
 * This function handles the main event loop, processing messages from the system and updating the game state accordingly.
 * It handles keyboard and mouse interrupts, updates the display, and manages the main menu and game states.
 * 
 * @return 0 on success, 1 on failure.
 */
int loop(){
  message msg;
  int ipc_status;
  int r;

  while( menu_state != LEAVE ) {
    
    if(menu_state == GAME){
      check_game_win(b);
    }

    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
      printf("driver_receive failed with: %d", r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:	
          if (msg.m_notify.interrupts & irq_set_mouse) {
            switch(menu_state){
              case GAME:
                mouse_game_handler(b);
                break;
              default:
                mouse_default_handler();
                break;
            }
          }
          if (msg.m_notify.interrupts & irq_set_kbd) { 
            switch(menu_state){
              case MENU:
                keyboard_menu_handler();
                break;
              case RULES:
                keyboard_default_handler();
                break;
              case CHOOSE_GAME:
                keyboard_level_handler();
              case GAME:
                keyboard_game_handler(b);
                break;
              case GAME_WIN:
                keyboard_game_handler(b);
                break;
              default:
                break;
            } 
          }
          if (msg.m_notify.interrupts & irq_set_timer) {
            switch(menu_state){
              case MENU:
                if (displayMainMenu()) return 1; 
                break;
              case RULES:
                if (displayRules()) return 1; 
                break;
              case CHOOSE_GAME:
                if (displayChooseGame()) return 1; 
                break;
              case GAME:
                timer_game_handler(b);
                if(draw_game_board(b)) return 1;
                break;
              case GAME_WIN:
                if(draw_game_win(b)) return 1;
                break;
              default:
                break;
            } 
          }
        default:
          break;
      }
    }
  }

  return 0;
}

/**
 * @brief Main function of the project, initializes and runs the main event loop.
 * 
 * This function initializes the system, runs the main event loop, and then performs cleanup.
 * 
 * @param argc Number of arguments.
 * @param argv Array of arguments.
 * @return 0 on success, 1 on failure.
 */
int (proj_main_loop)(int argc, char **argv) {
  if(start()){
    return 1;
  }

  if (loop()){
    if(end()){
      return 1;
    }
    return 1;
  }

  if(end()){
    return 1;
  }

  return 0;
}

#include <lcom/lcf.h>

#include <stdint.h>

#include "controller.h"

// ----------------------------------------------------------------------------------------

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

  if (vg_exit() != OK){
    return 1;
  }

  return 0;
}

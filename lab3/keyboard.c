#include <lcom/lcf.h>

#include <stdint.h>

#include "i8042.h"
#include "keyboard.h"

int hook_id;

void (kbc_ih)() {

    uint8_t status; 
    uint8_t code;

    if(util_sys_inb(KBC_ST_REG, &status)){
        return 1;
    }

    if(status && KBC_OBF){
        if(util_sys_inb(KBC_OUT_BUF, &code)){
            return 1;
        }
        if(!(status && (KBC_PARITY | KBC_TIME_OUT))){
            //kbd_print_scancode(bool make, uint8_t size, uint8_t bytes[])
        }
    }
}

int (keyboard_subscribe_int)(uint8_t *bit_no) {

  hook_id = KEYBOARD_IRQ;
  *bit_no = KEYBOARD_IRQ;

  if(sys_irqsetpolicy(KEYBOARD_IRQ, (IRQ_REENABLE|IRQ_EXCLUSIVE), &hook_id)){
    return 1;
  }

  return 0;
}

int (keyboard_unsubscribe_int)() {
  
  if(sys_irqrmpolicy(&hook_id)){
    return 1;
  }

  return 0;
}

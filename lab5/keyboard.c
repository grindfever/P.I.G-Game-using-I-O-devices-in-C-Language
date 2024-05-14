#include <lcom/lcf.h>

#include <stdint.h>

#include "keyboard.h"
#include "I8042.h"

int kbd_hook_id;
int pos = 0;
bool complete = true;
struct scan_code_stats scan_code;



int (kbc_subscribe_int)(uint8_t *bit_no) {

  kbd_hook_id = KEYBOARD_IRQ;
  *bit_no = KEYBOARD_IRQ;

  if(sys_irqsetpolicy(KEYBOARD_IRQ, (IRQ_REENABLE|IRQ_EXCLUSIVE), &kbd_hook_id)){
    return 1;
  }

  return 0;
}

int (kbc_unsubscribe_int)() {
  
  if(sys_irqrmpolicy(&kbd_hook_id)){
    return 1;
  }

  return 0;
}

int (keyboard_read_return)(uint8_t *data){
    uint8_t status;

    for(int tries = 20; tries > 0; tries--) {
        if(util_sys_inb(KBC_ST_REG, &status)){
            return 1;
        }
        
        /* loop while 8042 output buffer is empty */
        if(status & KBC_OBF && !(status & KBC_AUX) ) {
            if(util_sys_inb(KBC_OUT_BUF, data)){
                return 1;
            } 
            if ((status & (KBC_PARITY | KBC_TIME_OUT)) == 0 )
                return 0;
            else
                return 1;
        }
        //tickdelay(micros_to_ticks(WAIT_KBC));
    }

    return 1;
}

bool (keyboard_inc_code)() {
  return (scan_code.code[1] == KBC_FIRST_SCAN); // true if byte 0xE0 is in array's second spot
}

int (keyboard_esc_break)() {
  if (scan_code.code[0] == KBC_BREAK_ESC) // scancode byte is 0x81
    return 0;

  return 1;
}

void (kbc_ih)() {
    uint8_t code;

    if(complete){
      scan_code.size = 0;
      complete = false;
    }

    if(keyboard_read_return(&code)){
      return;
    }

    if(code == KBC_FIRST_SCAN){
      complete = false;
      scan_code.code[scan_code.size] = code;
      scan_code.size++;
    }
    else{
      complete = true;
      scan_code.code[scan_code.size] = code;
      scan_code.size++;
      scan_code.make_break = !(code & BIT(7));
    }
}


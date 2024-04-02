#include <lcom/lcf.h>

#include <stdint.h>

#include "i8042.h"
#include "mouse.h"
#include "kbc.h"

int mouse_hook_id;

int (mouse_subscribe_int)(uint8_t *bit_no) {

  mouse_hook_id = KBD_AUX_IRQ;
  *bit_no = KBD_AUX_IRQ;

  if(sys_irqsetpolicy(KBD_AUX_IRQ, IRQ_EXCLUSIVE, &mouse_hook_id)){
    return 1;
  }

  return 0;
}

int (mouse_unsubscribe_int)() {
  
  if(sys_irqrmpolicy(&mouse_hook_id)){
    return 1;
  }

  return 0;
}
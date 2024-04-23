#include <lcom/lcf.h>

#include <stdint.h>

#include "i8042.h"
#include "mouse.h"
#include "kbc.h"

static int mouse_hook_id;
static int counter = 0;
bool complete = true;
struct packet pack;

void (mouse_ih)(){
    uint8_t code;

    if(complete){
        counter = 0;
        complete = false;
    }

    if(kbc_read_return_mouse(&code)){
      return;
    }

    switch (counter){
        case 0:
            if(code & BIT(3)){
                pack.bytes[counter] = code;
                pack.lb = code & BIT(0);
                pack.rb = code & BIT(1);
                pack.mb = code & BIT(2);
                if(code & BIT(4)){
                    pack.delta_x = 0xFF00;
                }
                else pack.delta_x = 0;
                if(code & BIT(5)){
                    pack.delta_y = 0xFF00;
                }
                else pack.delta_y = 0;
                pack.x_ov = code & BIT(6);
                pack.y_ov = code & BIT(7);
                counter++;
            }
            break;
        case 1:
            pack.delta_x |= code;
            pack.bytes[counter] = code;
            counter++;
            break;
        case 2:
            pack.delta_y |= code;
            pack.bytes[counter] = code;
            counter++;
            complete = true;
            break;
    }
}

int (mouse_subscribe_int)(uint8_t *bit_no) {

  mouse_hook_id = KBD_AUX_IRQ;
  *bit_no = 5;
  mouse_hook_id = *bit_no;

  if(sys_irqsetpolicy(KBD_AUX_IRQ, (IRQ_REENABLE|IRQ_EXCLUSIVE), &mouse_hook_id)){
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

int (mouse_send_command)(uint8_t cmd){
  if(kbc_write_command(KBC_WRITE_MOUSE_BYTE)){
      return 1;
  }

  if(kbc_write_argument(cmd)){
    return 1;
  }

  uint8_t data;

  if(kbc_read_return_mouse(&data)){
    return 1;
  }

  if(data != 0xFA){
    return 1;
  }

  return 0;
}

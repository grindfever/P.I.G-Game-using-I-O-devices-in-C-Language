#include <lcom/lcf.h>

#include <stdint.h>

#include "i8042.h"
#include "mouse.h"
#include "kbc.h"

/** @brief Hook ID for mouse interrupts */
static int mouse_hook_id;

/** @brief Counter for the number of bytes read from the mouse */
static int counter = 0;

/** @brief Flag to indicate if a complete packet has been read */
bool mouse_complete = true;

/** @brief Structure to store the mouse packet */
struct packet pack;


uint8_t code;

/**
 * @brief Mouse interrupt handler.
 */
void (mouse_ih)() {

    if(mouse_complete) {
        counter = 0;
        mouse_complete = false;
    }

    if(kbc_read_return_mouse(&code)) {
        return;
    }

    switch (counter) {
        case 0:
            if(code & BIT(3)) {
                pack.bytes[counter] = code;
                pack.lb = code & BIT(0);
                pack.rb = code & BIT(1);
                pack.mb = code & BIT(2);
                if(code & BIT(4)) {
                    pack.delta_x = 0xFF00;
                }
                else pack.delta_x = 0;
                if(code & BIT(5)) {
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
            mouse_complete = true;
            break;
    }
}

/**
 * @brief Subscribes mouse interrupts.
 * 
 * @param bit_no Pointer to store the bit number to be set in the mask returned upon an interrupt.
 * @return 0 on success, 1 on failure.
 */
int (mouse_subscribe_int)(uint8_t *bit_no) {
    mouse_hook_id = KBD_AUX_IRQ;
    *bit_no = 5;
    mouse_hook_id = *bit_no;

    if(sys_irqsetpolicy(KBD_AUX_IRQ, (IRQ_REENABLE | IRQ_EXCLUSIVE), &mouse_hook_id)) {
        return 1;
    }

    return 0;
}

/**
 * @brief Unsubscribes mouse interrupts.
 * 
 * @return 0 on success, 1 on failure.
 */
int (mouse_unsubscribe_int)() {
    if(sys_irqrmpolicy(&mouse_hook_id)) {
        return 1;
    }

    return 0;
}

/**
 * @brief Sends a command to the mouse.
 * 
 * @param cmd The command to send to the mouse.
 * @return 0 on success, 1 on failure.
 */
int (mouse_send_command)(uint8_t cmd) {
    if(kbc_write_command(KBC_WRITE_MOUSE_BYTE)) {
        return 1;
    }

    if(kbc_write_argument(cmd)) {
        return 1;
    }

    uint8_t data;
    if(kbc_read_return_mouse(&data)) {
        return 1;
    }

    if(data != 0xFA) {
        return 1;
    }

    return 0;
}


int (mouse_check_full)(){
  if(counter == 3){
    counter = 0;
    return 1;
  }
  return 0;
}

int (mouse_overflow)() {
  if (code & (BIT(7) | BIT(6)))
    return 1;

  return 0;
}



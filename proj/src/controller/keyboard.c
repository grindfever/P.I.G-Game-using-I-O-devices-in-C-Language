#include <lcom/lcf.h>
#include <stdint.h>
#include "i8042.h"
#include "keyboard.h"
#include "kbc.h"

/** @brief Hook ID for keyboard interrupts */
int kbd_hook_id;

/** @brief Position indicator for the scan code array */
int pos = 0;

/** @brief Flag to indicate if a complete scan code has been read */
bool keyboard_complete = true;

/** @brief Structure to store the scan code stats */
struct scan_code_stats scan_code;

/**
 * @brief Keyboard interrupt handler.
 */
void (kbc_ih)() {
    uint8_t code;

    if (keyboard_complete) {
        scan_code.size = 0;
        keyboard_complete = false;
    }

    if (kbc_read_return_keyboard(&code)) {
        return;
    }

    if (code == KBC_FIRST_SCAN) {
        keyboard_complete = false;
        scan_code.code[scan_code.size] = code;
        scan_code.size++;
    } else {
        keyboard_complete = true;
        scan_code.code[scan_code.size] = code;
        scan_code.size++;
        scan_code.make_break = !(code & BIT(7));
    }
}

/**
 * @brief Subscribes keyboard interrupts.
 * 
 * @param bit_no Pointer to store the bit number to be set in the mask returned upon an interrupt.
 * @return 0 on success, 1 on failure.
 */
int (keyboard_subscribe_int)(uint8_t *bit_no) {
    kbd_hook_id = KEYBOARD_IRQ;
    *bit_no = KEYBOARD_IRQ;

    if (sys_irqsetpolicy(KEYBOARD_IRQ, (IRQ_REENABLE | IRQ_EXCLUSIVE), &kbd_hook_id)) {
        return 1;
    }

    return 0;
}

/**
 * @brief Unsubscribes keyboard interrupts.
 * 
 * @return 0 on success, 1 on failure.
 */
int (keyboard_unsubscribe_int)() {
    if (sys_irqrmpolicy(&kbd_hook_id)) {
        return 1;
    }

    return 0;
}

/**
 * @brief Enables keyboard interrupts.
 * 
 * @return 0 on success, 1 on failure.
 */
int (keyboard_enable_interrupts)() {
    if (kbc_write_command(KBC_READ_CMD)) {
        return 1;
    }

    uint8_t cmd_byte;
    if (kbc_read_return_keyboard(&cmd_byte)) {
        return 1;
    }

    if (kbc_write_command(KBC_WRITE_CMD)) {
        return 1;
    }

    if (kbc_write_argument(cmd_byte | BIT(0))) {
        return 1;
    }

    return 0;
}

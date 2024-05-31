#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <lcom/lcf.h>

#include <stdint.h>

/**
 * @brief Structure to store scan code statistics.
 */
struct scan_code_stats {
  bool make_break;  /**< Indicates if the scan code is a make or break code. */
  uint8_t code[2];  /**< Array to store the scan code. */
  int size;         /**< Size of the scan code. */
};

/**
 * @brief Keyboard interrupt handler.
 * 
 * This function handles keyboard interrupts, reads the scan code from the keyboard,
 * and updates the scan_code structure with the scan code data.
 */
void (kbc_ih)();

/**
 * @brief Subscribes keyboard interrupts.
 * 
 * This function subscribes to keyboard interrupts by setting the appropriate IRQ policy.
 * 
 * @param bit_no Pointer to store the bit number of the IRQ line.
 * @return Returns 0 on success, and 1 on failure.
 */
int (keyboard_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes keyboard interrupts.
 * 
 * This function unsubscribes keyboard interrupts by removing the appropriate IRQ policy.
 * 
 * @return Returns 0 on success, and 1 on failure.
 */
int (keyboard_unsubscribe_int)();

/**
 * @brief Enables keyboard interrupts.
 * 
 * This function enables keyboard interrupts by setting the appropriate command byte in the keyboard controller.
 * 
 * @return Returns 0 on success, and 1 on failure.
 */
int (keyboard_enable_interrupts)();

#endif /* KEYBOARD_H */

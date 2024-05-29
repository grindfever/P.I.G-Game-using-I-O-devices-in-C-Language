#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Structure to hold scan code statistics.
 */
struct scan_code_stats {
  bool make_break; /**< Indicates if the scan code is a make or break code. */
  uint8_t code[2]; /**< The scan code (up to 2 bytes). */
  int size;        /**< Size of the scan code. */
};

/**
 * @brief Keyboard interrupt handler.
 */
void (kbc_ih)();

/**
 * @brief Subscribes keyboard interrupts.
 * 
 * @param bit_no Pointer to store the bit number to be set in the mask returned upon an interrupt.
 * @return 0 on success, 1 on failure.
 */
int (keyboard_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes keyboard interrupts.
 * 
 * @return 0 on success, 1 on failure.
 */
int (keyboard_unsubscribe_int)();

/**
 * @brief Enables keyboard interrupts.
 * 
 * @return 0 on success, 1 on failure.
 */
int (keyboard_enable_interrupts)();

/**
 * @brief Increments the scan code index.
 * 
 * @return True if successfully incremented, false otherwise.
 */
bool (kbc_inc_code)();

/**
 * @brief Checks if the ESC break code was received.
 * 
 * @return 0 if ESC break code was received, 1 otherwise.
 */
int (kbc_esc_break)();

/**
 * @brief Gets the current key code.
 * 
 * @return The current key code.
 */
uint8_t (get_key_code)();

#endif /* KEYBOARD_H */

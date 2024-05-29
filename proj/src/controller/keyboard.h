

#include <lcom/lcf.h>
#include <stdint.h>

/**
 * @brief Structure to hold the status of the scan code.
 */
struct scan_code_stats {
  bool make_break; /**< True if it's a make code, false if it's a break code */
  uint8_t code[2]; /**< Array to store the scan code bytes */
  int size;        /**< Size of the scan code */
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



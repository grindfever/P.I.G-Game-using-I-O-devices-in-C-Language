#include <lcom/lcf.h>

#include <stdint.h>

/**
 * @brief Mouse interrupt handler.
 */
void (mouse_ih)();

/**
 * @brief Subscribes mouse interrupts.
 * 
 * @param bit_no Pointer to store the bit number to be set in the mask returned upon an interrupt.
 * @return 0 on success, 1 on failure.
 */
int (mouse_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes mouse interrupts.
 * 
 * @return 0 on success, 1 on failure.
 */
int (mouse_unsubscribe_int)();

/**
 * @brief Sends a command to the mouse.
 * 
 * @param cmd The command to send to the mouse.
 * @return 0 on success, 1 on failure.
 */
int (mouse_send_command)(uint8_t cmd);


/**
 * @brief Checks if the mouse packet is full.
 * 
 * @return 1 if the mouse packet is full, 0 otherwise.
 */
int (mouse_check_full)();

/**
 * @brief Checks for mouse data overflow.
 * 
 * @return 1 if there is an overflow, 0 otherwise.
 */
int (mouse_overflow)();


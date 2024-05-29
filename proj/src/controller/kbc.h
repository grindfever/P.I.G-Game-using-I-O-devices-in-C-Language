#include <lcom/lcf.h>

#include <stdint.h>
#include "i8042.h"

/**
 * @brief Reads the status from the KBC.
 * 
 * @param status Pointer to store the read status.
 * @return 0 on success, 1 on failure.
 */
int (kbc_read_status)(uint8_t *status);

/**
 * @brief Writes a command to the KBC.
 * 
 * @param cmd Command byte to write.
 * @return 0 on success, 1 on failure.
 */
int (kbc_write_command)(uint8_t cmd);

/**
 * @brief Reads data from the keyboard output buffer.
 * 
 * @param data Pointer to store the read data.
 * @return 0 on success, 1 on failure.
 */
int (kbc_read_return_keyboard)(uint8_t *data);

/**
 * @brief Reads data from the mouse output buffer.
 * 
 * @param data Pointer to store the read data.
 * @return 0 on success, 1 on failure.
 */
int (kbc_read_return_mouse)(uint8_t *data);

/**
 * @brief Writes an argument to the KBC.
 * 
 * @param arg Argument byte to write.
 * @return 0 on success, 1 on failure.
 */
int (kbc_write_argument)(uint8_t arg);



/**
 * @file utils.c
 * @brief Utility functions for bit manipulation and system I/O.
 */

#include <lcom/lcf.h>
#include <stdint.h>

/**
 * @brief Extracts the least significant byte (LSB) from a 16-bit value.
 * 
 * @param val The 16-bit value.
 * @param lsb Pointer to store the extracted LSB.
 * @return 0 on success, 1 if the lsb pointer is NULL.
 */
int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  if(lsb == NULL) {
    return 1;
  }
  *lsb = val;
  return 0;
}

/**
 * @brief Extracts the most significant byte (MSB) from a 16-bit value.
 * 
 * @param val The 16-bit value.
 * @param msb Pointer to store the extracted MSB.
 * @return 0 on success, 1 if the msb pointer is NULL.
 */
int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  if(msb == NULL) {
    return 1;
  }
  *msb = val >> 8;
  return 0;
}

/**
 * @brief Reads a byte from the specified I/O port.
 * 
 * @param port The I/O port to read from.
 * @param value Pointer to store the read value.
 * @return 0 on success, 1 if the value pointer is NULL or sys_inb fails.
 */
int (util_sys_inb)(int port, uint8_t *value) {
  if(value == NULL) {
    printf("Null pointer\n");
    return 1;
  }

  uint32_t temp; 
  if(sys_inb(port, &temp)) {
    printf("Error sys_inb\n");
    return 1;
  }

  *value = temp;
  return 0;
}

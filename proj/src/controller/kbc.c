#include <lcom/lcf.h>

#include <stdint.h>
#include "i8042.h"
#include "kbc.h"

/**
 * @brief Reads the status from the KBC.
 * 
 * @param status Pointer to store the read status.
 * @return 0 on success, 1 on failure.
 */
int (kbc_read_status)(uint8_t *status) {
    if (util_sys_inb(KBC_ST_REG, status)) {
        return 1;
    }
    return 0;
}

/**
 * @brief Writes a command to the KBC.
 * 
 * @param cmd Command byte to write.
 * @return 0 on success, 1 on failure.
 */
int (kbc_write_command)(uint8_t cmd) {
    uint8_t status;

    for (int tries = 20; tries > 0; tries--) {
        kbc_read_status(&status); /* assuming it returns OK */
        /* loop while 8042 input buffer is not empty */
        if ((status & KBC_IBF) == 0) {
            sys_outb(KBC_CMD_REG, cmd); /* no args command */
            return 0;
        }
        tickdelay(micros_to_ticks(WAIT_KBC)); // e.g. tickdelay()
    }

    return 1;
}

/**
 * @brief Reads data from the keyboard output buffer.
 * 
 * @param data Pointer to store the read data.
 * @return 0 on success, 1 on failure.
 */
int (kbc_read_return_keyboard)(uint8_t *data) {
    uint8_t status;

    for (int tries = 20; tries > 0; tries--) {
        if (util_sys_inb(KBC_ST_REG, &status)) {
            return 1;
        }
        
        /* loop while 8042 output buffer is empty */
        if (status & KBC_OBF && !(status & KBC_AUX)) {
            if (util_sys_inb(KBC_OUT_BUF, data)) {
                return 1;
            } 
            if ((status & (KBC_PARITY | KBC_TIME_OUT)) == 0) {
                return 0;
            } else {
                return 1;
            }
        }
        // tickdelay(micros_to_ticks(WAIT_KBC));
    }

    return 1;
}
l
/**
 * @brief Reads data from the mouse output buffer.
 * 
 * @param data Pointer to store the read data.
 * @return 0 on success, 1 on failure.
 */
int (kbc_read_return_mouse)(uint8_t *data) {
    uint8_t status;

    for (int tries = 20; tries > 0; tries--) {
        if (util_sys_inb(KBC_ST_REG, &status)) {
            return 1;
        }
        
        /* loop while 8042 output buffer is empty */
        if (status & KBC_OBF && (status & KBC_AUX)) {
            if (util_sys_inb(KBC_OUT_BUF, data)) {
                return 1;
            } 
            if ((status & (KBC_PARITY | KBC_TIME_OUT)) == 0) {
                return 0;
            } else {
                return 1;
            }
        }
        // tickdelay(micros_to_ticks(WAIT_KBC));
    }

    return 1;
}

/**
 * @brief Writes an argument to the KBC.
 * 
 * @param arg Argument byte to write.
 * @return 0 on success, 1 on failure.
 */
int (kbc_write_argument)(uint8_t arg) {
    uint8_t status;

    for (int tries = 20; tries > 0; tries--) {
        kbc_read_status(&status); /* assuming it returns OK */
        /* loop while 8042 input buffer is not empty */
        if ((status & KBC_IBF) == 0) {
            sys_outb(KBC_ARG_REG, arg); /* no args command */
            return 0;
        }
        tickdelay(micros_to_ticks(WAIT_KBC)); // e.g. tickdelay()
    }

    return 1;
}
#ifndef _LCOM_I8042_H
#define _LCOM_I8042_H

/* KEYBOARD */

#define KBC_OUT_BUF 0x60
#define KBC_ST_REG 0x64
#define KBC_CMD_REG 0x64
#define KBC_ARG_REG 0x60
#define WAIT_KBC 20000

#define KBC_OBF BIT(0)
#define KBC_IBF BIT(1)
#define KBC_INH BIT(4)
#define KBC_AUX BIT(5)
#define KBC_TIME_OUT BIT(6)
#define KBC_PARITY BIT(7)

#define KBC_BREAK_ESC 0x81
#define KBC_FIRST_SCAN 0xE0

#define KBC_READ_CMD 0x20
#define KBC_WRITE_CMD 0x60
#define KBC_CHECK 0xAA 
#define KBC_CHECK_ERROR 0xFC
#define KBC_CHECK_OK 0x55
#define KBC_CHECK_ERROR 0xFC
#define KBC_CHECK_INTERFACE 0xAB //0 = OK
#define KBC_DISABLE 0xAD
#define KBC_ENABLE 0xAE

#endif /* _LCOM_I8042_H */


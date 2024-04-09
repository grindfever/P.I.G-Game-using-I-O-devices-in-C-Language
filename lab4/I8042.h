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

//COMMAND BYTE
#define KBC_DIS BIT(4)
#define KBC_DIS2 BIT(5)
#define KBC_INT BIT(0)
#define KBC_INT2 BIT(1)

//MOUSE COMMANDS -> passed as arg of command 0xD4
#define KBC_RES_MOUSE 0xFF //Reset Mouse reset
#define KBC_RESEND_ERR 0xFE //Resend For serial communications errors
#define KBC_SET_DEF 0xF6 //Set Defaults Set default values
#define KBC_DIS_REP 0xF5 //Disable (Data Reporting) In stream mode, should be sent before any other command
#define KBC_EN_REP 0xF4 //Enable (Data Reporting) In stream mode only
#define KBC_SET_SAMPLE 0xF3 //Set Sample Rate Sets state sampling rate
#define KBC_SET_REMOTE 0xF0 //Set Remote Mode Send data on request only
#define KBC_READ_DATA 0xEB //Read Data Send data packet request
#define KBC_SET_STREAM 0xEA //Set Stream Mode Send data on events
#define KBC_GET_CONF 0xE9 //Status Request Get mouse configuration (3 bytes)
#define KBC_SET_RES 0xE8 //Set Resolution
#define KBC_SET_SCAL_ACCEL 0xE7 //Set Scaling 2:1 Acceleration mode
#define KBC_SET_SCAL_LIN 0xE6 //Set Scaling 1:1 Linear mode

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

#define KBC_DISABLE_MOUSE 0xA7 
#define KBC_ENABLE_MOUSE 0xA8 
#define KBC_CHECK_MOUSE 0xA9 //Check Mouse Interface Returns 0, if OK
#define KBC_WRITE_MOUSE_BYTE 0xD4 //Write Byte to Mouse Byte (A)


#endif /* _LCOM_I8042_H */


#include <lcom/lcf.h>

#include <stdint.h>
#include "i8042.h"

int (kbc_read_status)(uint8_t *status);

int (kbc_write_command)(uint8_t cmd);

int (kbc_read_return)(uint8_t *data);

int (kbc_write_argument)(uint8_t arg);

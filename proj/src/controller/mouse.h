#include <lcom/lcf.h>

#include <stdint.h>

void (mouse_ih)();

int (mouse_subscribe_int)(uint8_t *bit_no);

int (mouse_unsubscribe_int)();

int (mouse_send_command)(uint8_t cmd);

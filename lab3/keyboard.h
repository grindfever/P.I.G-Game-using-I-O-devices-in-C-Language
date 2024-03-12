#include <lcom/lcf.h>

#include <stdint.h>

bool loop = true;

void (kbc_ih)();

int (keyboard_subscribe_int)(uint8_t);

int (keyboard_unsubscribe_int)();
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <lcom/lcf.h>

#include <stdint.h>

struct scan_code_stats{
  bool make_break;
  uint8_t code[2];
  int size;
};

void (kbc_ih)();

int (keyboard_subscribe_int)(uint8_t *bit_no);

int (keyboard_unsubscribe_int)();

int (keyboard_enable_interrupts)();

#endif /* KEYBOARD_H */

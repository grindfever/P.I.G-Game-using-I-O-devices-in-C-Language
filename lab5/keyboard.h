
#include <stdbool.h>
#include <stdint.h>


struct scan_code_stats{
  bool make_break;
  uint8_t code[2];
  int size;
};

int(kbc_subscribe_int)(uint8_t *bit_no);

int(kbc_unsubscribe_int)();

int (keyboard_read_return)(uint8_t *data);

bool(keyboard_inc_code)();

int(keyboard_esc_break)();

void(kbc_ih)();





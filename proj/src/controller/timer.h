#ifndef TIMER_H
#define TIMER_H

#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

// Global variables
extern int hook_id;
extern uint32_t counter;

// Function prototypes
int (timer_set_frequency)(uint8_t timer, uint32_t freq);

int (timer_subscribe_int)(uint8_t *bit_no);

int (timer_unsubscribe_int)();

void (timer_int_handler)();

int (timer_get_conf)(uint8_t timer, uint8_t *st);

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field);

#endif // TIMER_H

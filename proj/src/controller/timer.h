#ifndef TIMER_H
#define TIMER_H

#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

// Global variables
extern int hook_id;
extern uint32_t counter;

/**
 * @brief Sets the frequency of the specified timer.
 * 
 * @param timer The timer to set the frequency for (0, 1, or 2).
 * @param freq The desired frequency in Hz.
 * @return 0 on success, 1 on failure (e.g., invalid timer or frequency).
 */
int (timer_set_frequency)(uint8_t timer, uint32_t freq);

/**
 * @brief Subscribes to timer interrupts.
 * 
 * @param bit_no Pointer to store the bit number to be set in the mask returned upon an interrupt.
 * @return 0 on success, 1 on failure.
 */
int (timer_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes from timer interrupts.
 * 
 * @return 0 on success, 1 on failure.
 */
int (timer_unsubscribe_int)();

/**
 * @brief Timer interrupt handler that increments the counter.
 */
void (timer_int_handler)();

/**
 * @brief Gets the configuration of the specified timer.
 * 
 * @param timer The timer to get the configuration of (0, 1, or 2).
 * @param st Pointer to store the status byte.
 * @return 0 on success, 1 on failure (e.g., invalid timer or NULL pointer).
 */
int (timer_get_conf)(uint8_t timer, uint8_t *st);

/**
 * @brief Displays the configuration of the specified timer.
 * 
 * @param timer The timer to display the configuration of (0, 1, or 2).
 * @param st The status byte of the timer.
 * @param field The field to interpret from the status byte.
 * @return 0 on success, 1 on failure (e.g., invalid field).
 */
int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field);
#endif // TIMER_H
